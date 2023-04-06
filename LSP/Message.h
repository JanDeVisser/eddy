/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include <core/Error.h>
#include <core/Logging.h>

#include <LSP/JSON.h>
#include <LSP/LSP.h>

namespace scratch::lsp {

using namespace Obelix;
using namespace std::literals;

using URI=std::string;
using DocumentUri=URI;
using string=std::string;
using boolean=bool;
using integer=int32_t;
using uinteger=uint32_t;
using decimal=double;

using LSPAny = JSONValue;
using LSPObject = JSONValue;
using LSPArray = JSONValue;

extern int s_next_request_id;

enum class ErrorCode {
    ParseError = -32700,
    InvalidRequest = -32600,
    MethodNotFound = -32601,
    InvalidParams = -32602,
    InternalError = -32603,

    /**
     * This is the start range of JSON-RPC reserved error codes.
     * It doesn't denote a real error code. No LSP error codes should
     * be defined between the start and end range. For backwards
     * compatibility the `ServerNotInitialized` and the `UnknownErrorCode`
     * are left in the range.
     *
     * @since 3.16.0
     */
    jsonrpcReservedErrorRangeStart = -32099,
    /** @deprecated use jsonrpcReservedErrorRangeStart */
    serverErrorStart = jsonrpcReservedErrorRangeStart,

    /**
     * Error code indicating that a server received a notification or
     * request before the server has received the `initialize` request.
     */
    ServerNotInitialized = -32002,
    UnknownErrorCode = -32001,

    /**
     * This is the end range of JSON-RPC reserved error codes.
     * It doesn't denote a real error code.
     *
     * @since 3.16.0
     */
    jsonrpcReservedErrorRangeEnd = -32000,
    /** @deprecated use jsonrpcReservedErrorRangeEnd */
    serverErrorEnd = jsonrpcReservedErrorRangeEnd,

    /**
     * This is the start range of LSP reserved error codes.
     * It doesn't denote a real error code.
     *
     * @since 3.16.0
     */
    lspReservedErrorRangeStart = -32899,

    /**
     * A request failed but it was syntactically correct, e.g the
     * method name was known and the parameters were valid. The error
     * message should contain human readable information about why
     * the request failed.
     *
     * @since 3.17.0
     */
    RequestFailed = -32803,

    /**
     * The server cancelled the request. This error code should
     * only be used for requests that explicitly support being
     * server cancellable.
     *
     * @since 3.17.0
     */
    ServerCancelled = -32802,

    /**
     * The server detected that the content of a document got
     * modified outside normal conditions. A server should
     * NOT send this error code if it detects a content change
     * in it unprocessed messages. The result even computed
     * on an older state might still be useful for the client.
     *
     * If a client decides that a result is not of any use anymore
     * the client should cancel the request.
     */
    ContentModified = -32801,

    /**
     * The client has canceled a request and a server as detected
     * the cancel.
     */
    RequestCancelled = -32800,

    /**
     * This is the end range of LSP reserved error codes.
     * It doesn't denote a real error code.
     *
     * @since 3.16.0
     */
    lspReservedErrorRangeEnd = -32800,
};

class DecodeError {
public:
    explicit DecodeError(std::string message)
        : m_message(std::move(message))
    {
    }

    explicit DecodeError(char const *msg)
        : m_message(msg)
    {
    }

    template <typename ...Args>
    explicit DecodeError(char const *msg, Args&&... args)
    {
        m_message = format(msg, std::forward<Args>(args)...);
    }

    [[nodiscard]] std::string const& message() const { return m_message; }

private:
    std::string m_message;
};

class Void {
public:
    Void() = default;

    static ErrorOr<Void,JSONDecodeError> decode_json(JSONValue const& obj)
    {
        if (!obj.is_null())
            return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
        return Void();
    }
};
using null=Void;

template<>
inline JSONValue to_json(Void const&)
{
    return {};
}

template <typename Object>
inline std::string method_name()
{
    fatal("No method name defined for object class '{}'", typeid(Object).name());
}

template <class Parameter>
class Message {
public:
    using ParameterClass = Parameter;
    Message<Parameter>() = default;
    explicit Message(Parameter parameter)
        : m_parameter(std::move(parameter))
    {
    }

    [[nodiscard]] Parameter const& parameter() const { return m_parameter; }

protected:
    Parameter m_parameter {};
};

template <class MessageClass, class Parameter=std::string>
requires std::derived_from<MessageClass, Message<Parameter>>
JSONValue to_json(MessageClass const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<Parameter>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    return msg;
}

class ResponseError {
public:
    ResponseError() = default;
    ResponseError(ErrorCode code, std::string message, JSONValue data = {})
        : code(static_cast<int>(code))
        , message(std::move(message))
        , data(std::move(data))
    {
    }

    ResponseError(int code, std::string message, JSONValue data = {})
        : code(code)
        , message(std::move(message))
        , data(std::move(data))
    {
    }

    template <typename ...Args>
    ResponseError(ErrorCode code, char const *msg, Args&&... args)
        : code(static_cast<int>(code))
    {
        message = format(msg, std::forward<Args>(args)...);
    }

    int code { 0 };
    std::string message {};
    JSONValue data {};

private:
};

template<>
ErrorOr<void, JSONDecodeError> decode_value(JSONValue const& value, ResponseError& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ResponseError" };
    TRY_RETURN(decode<int>(value, "code", target.code));
    TRY_RETURN(decode<std::string>(value, "message", target.message));
    return {};
}

template <class Result>
class Response : public Message<Result> {
public:
    [[nodiscard]] int id() const { return m_id; }
    [[nodiscard]] bool is_error() const { return m_error.has_value(); }
    [[nodiscard]] Result const& result() const { return Message<Result>::parameter(); }
    [[nodiscard]] ResponseError error() const { return *m_error; }

    static ErrorOr<Response,JSONDecodeError> decode_json(JSONValue const& obj)
    {
        Response result;
        TRY_RETURN(decode(obj, "id", result.m_id));
        TRY_RETURN(decode(obj, "error", result.m_error));
        if (!obj["result"].is_null()) {
            TRY_RETURN(decode<Result>(obj, "result", result.m_parameter));
        } else if (!result.m_error) {
            return JSONDecodeError { JSONDecodeError::Code::MissingValue, "result or error" };
        }
        return result;
    }

private:
    Response() = default;
    int m_id {0};
    std::optional<ResponseError> m_error {};
};

template <class Parameter, class Result>
class Request : public Message<Parameter> {
public:
    using ResultClass = Result;

    explicit Request(Parameter parameter)
        : Message<Parameter>(std::move(parameter))
        , m_id(get_next_id())
    {
    }

    Request()
        : Message<Parameter>()
        , m_id(get_next_id())
    {
    }

    [[nodiscard]] int id() const { return m_id; }

private:
    int get_next_id()
    {
        if (s_next_request_id < 0) {
            s_next_request_id = static_cast<int>(time(nullptr));
        }
        return s_next_request_id++;
    }

    int m_id;
};

template <class Parameter, class Result>
inline JSONValue to_json(Request<Parameter,Result> const& obj)
{
    auto ret = to_json<Message<Parameter>>(obj);
    ret.set("id", obj.id());
    return ret;
}

template <class RequestClass>
inline ErrorOr<Response<typename RequestClass::ResultClass>, JSONDecodeError> decode_response(JSONValue const&)
{
    fatal("Specialize decode_response<{}>()", typeid(RequestClass).name());
}

template <class RequestClass>
ErrorOr<Response<typename RequestClass::ResultClass>, JSONDecodeError> send_request(LSP& endpoint, typename RequestClass::ParameterClass params)
{
    RequestClass req { std::move(params) };
    auto err_maybe = endpoint.send(to_json<RequestClass>(req));
    if (err_maybe.is_error())
        return JSONDecodeError { JSONDecodeError::Code::ProtocolError, err_maybe.error().to_string() };
    auto response_maybe = endpoint.receive();
    if (response_maybe.is_error())
        return JSONDecodeError { JSONDecodeError::Code::ProtocolError, response_maybe.error().to_string() };
    auto response = response_maybe.value();

    auto result = TRY(decode_response<RequestClass>(response));
    if (result.id() != req.id()) {
        return JSONDecodeError { JSONDecodeError::Code::UnexpectedValue, "id" };
    }
    return result;
}

template <class RequestClass>
ErrorOr<Response<typename RequestClass::ResultClass>, JSONDecodeError> send_request(LSP& endpoint)
{
    RequestClass req;
    auto err_maybe = endpoint.send(to_json<RequestClass>(req));
    if (err_maybe.is_error())
        return JSONDecodeError { JSONDecodeError::Code::ProtocolError, err_maybe.error().to_string() };
    auto response_maybe = endpoint.receive();
    if (response_maybe.is_error())
        return JSONDecodeError { JSONDecodeError::Code::ProtocolError, response_maybe.error().to_string() };
    auto response = response_maybe.value();

    auto result = TRY(decode_response<RequestClass>(response));
    if (result.id() != req.id()) {
        return JSONDecodeError { JSONDecodeError::Code::UnexpectedValue, "id" };
    }
    return result;
}

template <class Parameter=std::string>
class Notification : public Message<Parameter> {
public:
    explicit Notification(Parameter params)
        : Message<Parameter>(std::move(params))
    {
    }
    Notification() = default;
};

template <class Parameter>
inline JSONValue to_json(Notification<Parameter> const& obj)
{
    auto msg = to_json<Message<Parameter>>(obj);
    msg.set("method", method_name<Notification<Parameter>>());
    return msg;
}

template <class NotificationClass>
ErrorOr<void, JSONDecodeError> send_notification(LSP& endpoint, typename NotificationClass::ParameterClass params)
{
    NotificationClass notification { std::move(params) };
    auto ret_maybe = endpoint.send(to_json<NotificationClass>(notification));
    if (ret_maybe.is_error())
        return JSONDecodeError { JSONDecodeError::Code::ProtocolError, ret_maybe.error().to_string() };
    return {};
}

template <class NotificationClass>
ErrorOr<void, JSONDecodeError> send_notification(LSP& endpoint)
{
    NotificationClass notification;
    auto ret_maybe = endpoint.send(to_json<NotificationClass>(notification));
    if (ret_maybe.is_error())
        return JSONDecodeError { JSONDecodeError::Code::ProtocolError, ret_maybe.error().to_string() };
    return {};
}

}
