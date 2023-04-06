/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "JSON.h"
#include "lexer/Lexer.h"

namespace scratch::lsp {

[[nodiscard]] std::string JSONValue::to_string() const
{
    switch (type()) {
    case JSONType::Null:
        return "null";
    case JSONType::String:
        return std::get<std::string>(m_value);
    case JSONType::Integer:
        return std::to_string(std::get<int64_t>(m_value));
    case JSONType::Boolean:
        return std::get<bool>(m_value) ? "true" : "false";
    case JSONType::Double:
        return std::to_string(std::get<double>(m_value));
    case JSONType::Array: {
        auto const& array = std::get<Array>(m_value);
        if (array.empty())
            return "[]";
        std::string ret = "[ ";
        bool first = true;
        for (auto const& v : array) {
            if (!first)
                ret += ", ";
            first = false;
            ret += v.serialize();
        }
        return ret + " ]";
    }
    case JSONType::Object: {
        auto const& object = std::get<Object>(m_value);
        if (object.empty())
            return "{}";
        std::string ret = "{ ";
        bool first = true;
        for (auto const& v : object) {
            if (!first)
                ret += ", ";
            first = false;
            ret += "\"" + v.first + "\": " + v.second.serialize();
        }
        return ret + " }";
    }
    }
}

[[nodiscard]] std::string JSONValue::serialize(bool pretty, int indent_width, int indent) const
{
    switch (type()) {
    case JSONType::Null:
    case JSONType::Integer:
    case JSONType::Double:
    case JSONType::Boolean:
        return to_string();
    case JSONType::String:
        return "\"" + to_string() + "\"";
    case JSONType::Array: {
        auto const& array = std::get<Array>(m_value);
        if (array.empty())
            return "[]";
        std::string ret = "[";
        bool first = true;
        for (auto const& v : array) {
            if (!first)
                ret += ",";
            if (pretty) {
                ret += "\n";
                for (auto i = 0u; i < indent + indent_width; ++i) ret += ' ';
            } else {
                ret += ' ';
            }
            first = false;
            ret += v.serialize(pretty, indent_width, indent + indent_width);
        }
        if (pretty) {
            ret += "\n";
            for (auto i = 0u; i < indent; ++i) ret += ' ';
        } else {
            ret += ' ';
        }
        return ret + "]";
    }
    case JSONType::Object: {
        auto const& object = std::get<Object>(m_value);
        if (object.empty())
            return "{}";
        std::string ret = "{";
        bool first = true;
        for (auto const& v : object) {
            if (!first)
                ret += ",";
            first = false;
            if (pretty) {
                ret += "\n";
                for (auto i = 0u; i < indent + indent_width; ++i) ret += ' ';
            } else {
                ret += ' ';
            }
            ret += "\"" + v.first + "\": " + v.second.serialize();
        }
        if (pretty) {
            ret += "\n";
            for (auto i = 0u; i < indent; ++i) ret += ' ';
        } else {
            ret += ' ';
        }
        return ret + "}";
    }
    }
}

ErrorOr<JSONValue,JSONValue::ParseError> JSONValue::deserialize(std::string const& str)
{
    JSONValue current;
    std::vector<JSONValue> state {};

    StringBuffer sb { str };
    Lexer lexer { sb };
    lexer.add_scanner<Obelix::QStringScanner>("\"'", false);
    lexer.add_scanner<Obelix::NumberScanner>(Obelix::NumberScanner::Config { true, true, true, false, true });
    lexer.add_scanner<Obelix::WhitespaceScanner>();
    lexer.add_scanner<Obelix::KeywordScanner>(
        TokenCode::Keyword0, "null",
        TokenCode::Keyword1, "true",
        TokenCode::Keyword2, "false");
    for (auto const& token : lexer.tokenize()) {
        bool handled { false };
        current = {};
        switch (token.code()) {
        case TokenCode::Keyword0:
            break;
        case TokenCode::Keyword1:
            current = JSONValue(true);
            break;
        case TokenCode::Keyword2:
            current = JSONValue(false);
            break;
        case TokenCode::UnclosedDoubleQuotedString:
            return ParseError::Error;
        case TokenCode::DoubleQuotedString:
            current = JSONValue(token.string_value());
            break;
        case TokenCode::Integer:
        case TokenCode::HexNumber:
            current = JSONValue(token.to_long().value());
            break;
        case TokenCode::Float:
            current = JSONValue(token.to_double().value());
            break;
        case TokenCode::OpenBracket:
            state.emplace_back(JSONType::Array);
            handled = true;
            break;
        case TokenCode::CloseBracket:
            if (state.empty() || !state.back().is_array())
                return ParseError::Error;
            current = state.back();
            state.pop_back();
            break;
        case TokenCode::OpenBrace:
            state.emplace_back(JSONType::Object);
            handled = true;
            break;
        case TokenCode::CloseBrace:
            if (state.empty() || !state.back().is_object())
                return ParseError::Error;
            current = state.back();
            state.pop_back();
            break;
        case TokenCode::Comma:
            if (state.empty() || (!state.back().is_object() && !state.back().is_array()))
                return ParseError::Error;
            handled = true;
            break;
        case TokenCode::Colon:
            if (state.empty() || !state.back().is_string())
                return ParseError::Error;
            handled = true;
            break;
        case TokenCode::EndOfFile:
            handled = true;
            break;
        default:
            return ParseError::Error;
        }

        if (handled)
            continue;

        if (state.empty()) {
            state.push_back(current);
            continue;
        }

        auto& last = state.back();
        if (last.is_array()) {
            last.append(current);
            continue;
        }

        if (last.is_object()) {
            if (!current.is_string())
                return ParseError::Error;
            state.push_back(current);
            continue;
        }

        if (last.is_string() && (state.size() >= 2) && state[state.size()-2].is_object()) {
            auto& obj = state[state.size()-2];
            obj.set(std::get<std::string>(last.m_value), current);
            state.pop_back();
            continue;
        }

        return ParseError::Error;
    }
    if (state.empty())
        return JSONValue();
    return state.back();
}

} // Obelix
