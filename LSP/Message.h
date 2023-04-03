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

class MessageParameter {
public:
    [[nodiscard]] virtual JSONValue to_json() const = 0;
};

class Void {
public:
    Void() = default;
};

template <typename Object>
inline JSONValue to_json(Object const& obj)
{
    return {};
}

template <typename Parameter>
requires std::derived_from<Parameter,MessageParameter>
inline JSONValue to_json(Parameter const& obj)
{
    return (&obj)->to_json();
}

template <>
inline JSONValue to_json(std::string const& obj)
{
    return {};
}

template <typename Object>
inline std::string method_name(Object const&)
{
    fatal("No method name defined for object class '{}'", typeid(Object).name());
}

template <>
inline std::string method_name(std::string const& obj)
{
    return obj;
}

template <class Parameter>
class Message {
public:
    Message<Parameter>() = default;
    explicit Message(Parameter parameter)
        : m_parameter(std::move(parameter))
    {
    }

    [[nodiscard]] Parameter const& parameter() const { return m_parameter; }

private:
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

template <class Parameter=std::string>
class Request : public Message<Parameter> {
public:
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

template <class Parameter>
inline JSONValue to_json(Request<Parameter> const& obj)
{
    auto msg = to_json<Message<Parameter>>(obj);
    msg.set("id", JSONValue(obj.id()));
    msg.set("method", method_name<Parameter>(obj.parameter()));
    return msg;
}

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

template <class Result>
ErrorOr<Result,DecodeError> decode(JSONValue const&)
{
    return DecodeError { "Please implement decode for Result class '{}'", typeid(Result).name() };
}

ErrorOr<Void,DecodeError> decode(JSONValue const& obj)
{
    if (!obj.is_null())
        return DecodeError { "Cannot decode json value '{}' to Void", obj.encode() };
    return Void {};
}

class ResponseError {
public:
    ResponseError() = default;
    ResponseError(ErrorCode code, std::string message, JSONValue data = {})
        : m_code(static_cast<int>(code))
        , m_message(std::move(message))
        , m_data(std::move(data))
    {
    }

    ResponseError(int code, std::string message, JSONValue data = {})
        : m_code(code)
        , m_message(std::move(message))
        , m_data(std::move(data))
    {
    }

    template <typename ...Args>
    ResponseError(ErrorCode code, char const *msg, Args&&... args)
        : m_code(static_cast<int>(code))
    {
        m_message = format(msg, std::forward<Args>(args)...);
    }

    [[nodiscard]] int code() const { return m_code; }
    [[nodiscard]] std::string const& message() const { return m_message; }
    [[nodiscard]] JSONValue const& data() const { return m_data; }

private:
    int m_code { 0 };
    std::string m_message {};
    JSONValue m_data {};
};

template<>
ErrorOr<ResponseError,DecodeError> decode(JSONValue const& msg)
{
    auto code = msg["code"];
    if (!code.is_integer())
        fatal("Received ResponseError without code: {}", msg.encode());
    auto message = msg["message"];
    if (!message.is_string())
        fatal("Received ResponseError without message: {}", msg.encode());
    return ResponseError { *(code.to_int<int>()), message.to_string(), msg["data"] };
}

template <class Result>
class Response : public Message<Result> {
public:
    Response(int id, Result result)
        : Message<Result>()
        , m_id(id)
    {
    }
    Response(int id, ResponseError error)
        : Message<Result>()
        , m_id(id)
        , m_error(std::move(error))
    {
    }

    [[nodiscard]] int id() const { return m_id; }
    [[nodiscard]] bool is_error() const { return m_error.has_value(); }
    [[nodiscard]] Result const& result() const { return Message<Result>::parameter(); }
    [[nodiscard]] ResponseError error() const { return *m_error; }

private:
    int m_id;
    std::optional<ResponseError> m_error {};
};

template <class Parameter=std::string>
class Notification : public Message<Parameter> {
public:
    explicit Notification(Parameter parameter)
        : Message<Parameter>(std::move(parameter))
    {
    }
    Notification() = default;
};

template <class Parameter>
inline JSONValue to_json(Notification<Parameter> const& obj)
{
    auto msg = to_json<Message<Parameter>>(obj);
    msg.set("method", method_name<Parameter>(obj.parameter()));
    return msg;
}

template <class Parameter, class Result>
ErrorOr<Response<Result>, SystemError> send_request(LSP& endpoint, Parameter parameter)
{
    Request<Parameter> msg { std::move(parameter) };
    TRY_RETURN(endpoint.send(to_json(msg)));
    auto response = TRY(endpoint.receive());

    if (!response.has("id")) {
        return Response<Result> { -1, { ErrorCode::ParseError, "Received response without id: {}", response.encode() } };
    }
    auto id_value = response["id"];
    if (!id_value.is_integer()) {
        return Response<Result> { -1, { ErrorCode::ParseError, "Received response with of wrong type: {}", id_value.to_string() } };
    }
    auto id = *id_value.to_int<int>();
    if (id != msg.id()) {
        return Response<Result> { id, { ErrorCode::InternalError, "Received request for id '{}' but expected '{}'", id, msg.id() } };
    }
    if (!response["result"].is_null()) {
        auto result = decode<Result>(response["result"]);
        if (result.is_error())
            return Response<Result> { id, { ErrorCode::ParseError, result.error().message() } };
        return Response<Result> { id, result.value() };
    }
    if (!response["error"].is_null()) {
        auto response_error = decode<ResponseError>(response["error"]);
        if (response_error.is_error())
            return Response<Result> { id, { ErrorCode::ParseError, response_error.error().message() } };
        return Response<Result> { id, response_error.value() };
    }
    return Response<Result> { id, { ErrorCode::ParseError, "Response for request '{}' has neither result nor error" } };
}

template <class Parameter>
ErrorOr<void, SystemError> send_notification(LSP& endpoint, Parameter parameter)
{
    Notification<Parameter> msg { std::move(parameter) };
    return endpoint.send(to_json(msg));
}

}
