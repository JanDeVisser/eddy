/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <variant>

#include <Core/Error.h>
#include <Core/Logging.h>

#pragma once

namespace eddy::lsp {

using namespace Obelix;

template<typename T>
concept Boolean = std::is_same_v<std::remove_cvref_t<T>, bool>;

template<typename T>
concept Integer = (std::is_integral_v<T> && !Boolean<T>);

struct JSONDecodeError {
    enum class Code {
        NoSuchKey,
        TypeMismatch,
        MissingValue,
        UnexpectedValue,
        ProtocolError,
    };
    Code code;
    std::string key;
};

enum class JSONType {
    Null,
    String,
    Integer,
    Boolean,
    Double,
    Array,
    Object,
};

class JSONValue {
public:
    using Array = std::vector<JSONValue>;
    using Object = std::map<std::string, JSONValue>;

    enum class ParseError {
        NoError,
        Error,
    };

    JSONValue() = default;

    JSONValue(JSONType type)
        : m_type(type)
    {
        switch (m_type) {
        case JSONType::Null:
        case JSONType::Integer:
            m_value = 0;
            break;
        case JSONType::Boolean:
            m_value = false;
            break;
        case JSONType::String:
            m_value = "";
            break;
        case JSONType::Double:
            m_value = 0.0;
            break;
        case JSONType::Array:
            m_value = Array();
            break;
        case JSONType::Object:
            m_value = Object();
            break;
        }
    }

    JSONValue(std::string value)
        : m_type(JSONType::String)
        , m_value(std::move(value))
    {
    }

    JSONValue(std::string_view value)
        : m_type(JSONType::String)
        , m_value(std::string(value))
    {
    }

    JSONValue(char const* value)
        : m_type(JSONType::String)
        , m_value(value)
    {
    }

    template <Integer Int>
    JSONValue(Int value)
        : m_type(JSONType::Integer)
        , m_value(value)
    {
    }

    template<Boolean B>
    JSONValue(B value)
        : m_type(JSONType::Boolean)
        , m_value(value)
    {
    }

    template <std::floating_point Float>
    JSONValue(Float value)
        : m_type(JSONType::Double)
        , m_value(value)
    {
    }

    [[nodiscard]] JSONType type() const { return m_type; }
    [[nodiscard]] bool is_null() const { return m_type == JSONType::Null; }
    [[nodiscard]] bool is_string() const { return m_type == JSONType::String; }
    [[nodiscard]] bool is_integer() const { return m_type == JSONType::Integer; }
    [[nodiscard]] bool is_boolean() const { return m_type == JSONType::Boolean; }
    [[nodiscard]] bool is_double() const { return m_type == JSONType::Double; }
    [[nodiscard]] bool is_array() const { return m_type == JSONType::Array; }
    [[nodiscard]] bool is_object() const { return m_type == JSONType::Object; }

    static JSONValue array()
    {
        return { JSONType::Array };
    }

    static JSONValue object()
    {
        return { JSONType::Object };
    }

    friend std::ostream& operator<<(std::ostream& os, const JSONValue& value)
    {
        os << value.serialize();
        return os;
    }

    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] std::string serialize(bool pretty = false, int indent_width = 4, int indent = 0) const;

    template <Integer Int>
    std::optional<Int> to_int() const
    {
        switch (m_type) {
        case JSONType::Integer:
            return static_cast<Int>(std::get<int64_t>(m_value));
        case JSONType::Double:
            return static_cast<Int>(std::get<double>(m_value));
        case JSONType::Boolean:
            return std::get<bool>(m_value) ? 1 : 0;
        default:
            return {};
        }
    }

    template <std::floating_point Float>
    std::optional<Float> to_float() const
    {
        switch (m_type) {
        case JSONType::Integer:
            return static_cast<Float>(std::get<int64_t>(m_value));
        case JSONType::Double:
            return static_cast<Float>(std::get<double>(m_value));
        default:
            return {};
        }
    }

    template <Boolean B=bool>
    std::optional<B> to_boolean() const
    {
        switch (m_type) {
        case JSONType::Null:
            return false;
        case JSONType::Integer:
            return std::get<int64_t>(m_value) != 0;
        case JSONType::Boolean:
            return std::get<bool>(m_value);
        default:
            return {};
        }
    }

    template <typename Target>
    ErrorOr<Target,JSONDecodeError> convert() const
    {
        if (!is_object())
            return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
        return Target::decode_json(*this);
    }

    template <Integer Int>
    ErrorOr<Int,JSONDecodeError> convert() const
    {
        auto value = to_int<Int>();
        if (!value)
            return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
        return *value;
    }

    template <>
    ErrorOr<std::string,JSONDecodeError> convert() const
    {
        return to_string();
    }

    template <Boolean Bool>
    ErrorOr<Bool,JSONDecodeError> convert() const
    {
        auto value = to_boolean<Bool>();
        if (!value)
            return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
        return *value;
    }

    template <std::floating_point Float>
    ErrorOr<Float,JSONDecodeError> convert() const
    {
        auto value = to_float<Float>();
        if (!value)
            return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
        return *value;
    }

    [[nodiscard]] std::optional<Array> to_array() const
    {
        if (m_type != JSONType::Array)
            return {};
        return std::get<Array>(m_value);
    }

    [[nodiscard]] std::optional<Object> to_object() const
    {
        if (m_type != JSONType::Object)
            return {};
        return std::get<Object>(m_value);
    }

    void append(JSONValue const& value)
    {
        if (m_type != JSONType::Array)
            return;
        auto& array = std::get<Array>(m_value);
        array.push_back(value);
    }

    void set(std::string const& key, JSONValue const& value)
    {
        if (m_type != JSONType::Object)
            return;
        auto& object = std::get<Object>(m_value);
        object[key] = value;
    }

    size_t size() const
    {
        switch (m_type) {
        case JSONType::Array:
            return std::get<Array>(m_value).size();
        case JSONType::Object:
            return std::get<Object>(m_value).size();
        default:
            return 0;
        }
    }

    [[nodiscard]] bool has(std::string const& key) const
    {
        if (m_type != JSONType::Object)
            return false;
        auto& object = std::get<Object>(m_value);
        return object.contains(key);
    }

    [[nodiscard]] std::optional<JSONValue> get(std::string const& key) const
    {
        if (m_type != JSONType::Object)
            return {};
        auto& object = std::get<Object>(m_value);
        if (object.contains(key))
            return object.at(key);
        return {};
    }

    JSONValue operator[](std::string const& key) const
    {
        assert(m_type == JSONType::Object);
        auto value = get(key);
        if (value.has_value())
            return *value;
        return {};
    }

    [[nodiscard]] std::optional<JSONValue> get(uint ix) const
    {
        if (m_type != JSONType::Array)
            return {};
        auto& array = std::get<Array>(m_value);
        if (ix < array.size())
            return array[ix];
        return {};
    }

    JSONValue operator[](uint ix) const
    {
        assert(m_type == JSONType::Array);
        auto value = get(ix);
        if (value.has_value())
            return *value;
        return {};
    }

    JSONValue& merge(JSONValue const& other)
    {
        assert(is_object() && other.is_object());
        auto const& obj = std::get<Object>(other.m_value);
        for (auto const& [name, value] : obj) {
            set(name, value);
        }
        return *this;
    }

    static ErrorOr<JSONValue,JSONValue::ParseError> deserialize(std::string const&);

private:
    JSONType m_type { JSONType::Null };
    std::variant<std::string, int64_t, bool, double, Array, Object> m_value;
};

template <typename T>
inline JSONValue to_json(T const&)
{
    return {};
}

template <>
inline JSONValue to_json(std::string const& obj)
{
    return { obj };
}

template <Integer Int>
inline JSONValue to_json(Int const& value)
{
    return { value };
}

template <Boolean B>
inline JSONValue to_json(B const& value)
{
    return { value };
}

template <std::floating_point Float>
inline JSONValue to_json(Float const& value)
{
    return { value };
}

template <typename Element>
inline JSONValue to_json(std::vector<Element> const& value)
{
    JSONValue ret = JSONValue::array();
    for (auto const& elem : value) {
        ret.append(to_json<Element>(elem));
    }
    return ret;
}

template <typename Value>
inline JSONValue to_json(std::map<std::string, Value> const& value)
{
    JSONValue ret = JSONValue::object();
    for (auto const& [key, v] : value) {
        ret.set(key, to_json<Value>(v));
    }
    return ret;
}

template <typename T>
inline JSONValue to_json(std::optional<T> const& value)
{
    if (value)
        return to_json(*value);
    return {};
}

template <int N,typename ...Ts>
inline JSONValue to_json(std::variant<Ts...> const& value)
{
    if (N == value.index()) {
        return to_json(std::get<N, Ts...>(value));
    }
    if constexpr (N < (sizeof...(Ts)-1)) {
        return to_json<N + 1, Ts...>(value);
    }
}

template <typename T>
inline void set(JSONValue& obj, std::string const& key, T const& value)
{
    assert(obj.is_object());
    obj.set(key, to_json(value));
}

template <typename T>
inline void set(JSONValue& obj, std::string const& key, std::optional<T> const& value)
{
    assert(obj.is_object());
    if (value.has_value()) {
        auto const& v = value.value();
        set(obj, key, v);
    }
}

template <typename T>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, T& target)
{
    fatal("Specialize decode_value(JSONValue, {})", to_string<std::type_info>()(typeid(decltype(target))));
}

template <Integer Int>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Int& target)
{
    if (!value.is_integer())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = *(value.to_int<Int>());
    return {};
}

template <Boolean Bool>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Bool& target)
{
    if (!value.is_boolean())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = *(value.to_boolean());
    return {};
}

template <std::floating_point Float>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Float& target)
{
    if (!value.is_double())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = *(value.to_float<Float>());
    return {};
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, std::string& target)
{
    if (!value.is_string())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = value.to_string();
    return {};
}

template <typename T>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, std::vector<T>& target)
{
    if (!value.is_array())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    for (auto ix = 0u; ix < value.size(); ++ix) {
        T decoded;
        TRY_RETURN(decode_value<T>(value[ix], decoded));
        target.push_back(decoded);
    }
    return {};
}

template <typename T>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, std::map<std::string,T>& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    auto map = *(value.to_object());
    for (auto const& [k, _] : map) {
        T decoded;
        TRY_RETURN(decode<T>(value, k, decoded));
        target[k] = decoded;
    }
    return {};
}

template <int N, typename ...Ts>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, std::variant<Ts...>& target)
{
    using V = std::variant<Ts...>;
    using T=std::variant_alternative_t<N, V>;
    T v;
    auto converted_maybe = decode_value<T>(value, v);
    if (!converted_maybe.is_error()) {
        target.template emplace<N>(v);
        return {};
    }
    if constexpr (N > 0)
        return decode_value<N-1,Ts...>(value, target);
    return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
}

template <typename ...Ts>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, std::variant<Ts...>& target)
{
//    std::cerr << "decode_value<std::variant<" << to_string<std::type_info>()(typeid(decltype(target))) << ">()\n";
    return decode_value<sizeof...(Ts)-1, Ts...>(value, target);
}

template <typename T>
inline ErrorOr<void,JSONDecodeError> decode(JSONValue const& obj, std::string const& key, T& target)
{
//    std::cerr << "decode<" << to_string<std::type_info>()(typeid(decltype(target))) << ">(" << key << ")\n";
    assert(obj.is_object());
    auto value = obj.get(key);
    if (!value)
        return JSONDecodeError { JSONDecodeError::Code::NoSuchKey, key };
    auto err_maybe = decode_value(*value, target);
    if (err_maybe.is_error()) {
        auto err = err_maybe.error();
        err.key = key;
        return err;
    }
    return {};
}

template <typename T>
inline ErrorOr<void,JSONDecodeError> decode(JSONValue const& obj, std::string const& key, std::optional<T>& target)
{
//    std::cerr << "decode<std::optional<" << to_string<std::type_info>()(typeid(decltype(target))) << ">>(" << key << ")\n";
    assert(obj.is_object());
    auto value = obj.get(key);
    if (!value) {
        target.reset();
        return {};
    }
    T decoded;
    TRY_RETURN(decode(obj, key, decoded));
    target = decoded;
    return {};
}

}
