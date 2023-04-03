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

#include "core/Error.h"

#pragma once

namespace Obelix {

enum class JSONType {
    Null,
    String,
    Integer,
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

    template <std::integral Int>
    JSONValue(Int value)
        : m_type(JSONType::Integer)
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
        os << value.encode();
        return os;
    }

    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] std::string encode(bool pretty = false, int indent_width = 4, int indent = 0) const;

    template <std::integral Int>
    std::optional<Int> to_int() const
    {
        switch (m_type) {
        case JSONType::Integer:
            return static_cast<Int>(std::get<int64_t>(m_value));
        case JSONType::Double:
            return static_cast<Int>(std::get<double>(m_value));
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

    static ErrorOr<JSONValue,ParseError> decode(std::string const&);

private:
    JSONType m_type { JSONType::Null };
    std::variant<std::string, int64_t, double, Array, Object> m_value;
};

}
