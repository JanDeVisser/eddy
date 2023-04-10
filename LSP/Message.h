/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <future>

#include <core/Error.h>
#include <core/Logging.h>

#include <LSP/JSON.h>

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

template<>
inline ErrorOr<void, JSONDecodeError> decode_value(JSONValue const& value, Void& target)
{
    if (!value.is_null())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Void" };
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
inline ErrorOr<void, JSONDecodeError> decode_value(JSONValue const& value, ResponseError& target)
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

}
