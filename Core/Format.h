/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include "StringBuffer.h"
#include "StringUtil.h"

namespace Obelix {

class FormatSpecifier {
public:
    enum class FormatState {
        String,
        FormatMaybe,
        Format,
        Escape
    };

    enum class FormatSpecifierType {
        Default = ' ',
        String = 's',
        Int = 'd',
        Character = 'c',
        General = 'g',
        FixedPoint = 'f',
        Scientific = 'e',
        Percentage = '%',
        LocaleAware = 'n',
    };

    enum class FormatSpecifierAlignment {
        Left = '<',
        Right = '>',
        Center = '^',
        RightButSignLeft = '=',
    };

    enum class CaseCoercion {
        DontCare,
        ToUpper,
        ToLower,
    };

    enum class DisplaySign {
        OnlyForNegative = '-',
        Always = '+',
        SpaceForPositive = ' ',
    };

    enum class GroupingOption {
        None,
        Comma,
        Underscore,
    };

    [[nodiscard]] FormatSpecifierType type() const { return m_type; }
    [[nodiscard]] int width() const { return m_width; }
    [[nodiscard]] int precision() const { return m_precision; }
    [[nodiscard]] int base() const { return m_base; }
    [[nodiscard]] FormatSpecifierAlignment alignment() const { return m_alignment; }
    [[nodiscard]] size_t start() const { return m_start; }
    [[nodiscard]] size_t length() const { return m_length; }

    [[nodiscard]] std::string left_align(std::string const& str, size_t width) const
    {
        auto ret = str;
        while (ret.length() < width)
            ret.append(m_fill);
        return ret;
    }

    [[nodiscard]] std::string right_align(std::string const& str, size_t width) const
    {
        auto ret = str;
        while (ret.length() < width)
            ret.insert(0, m_fill);
        return ret;
    }

    [[nodiscard]] std::string center(std::string const& str, size_t width) const
    {
        auto ret = str;
        while (ret.length() < width) {
            ret.insert(0, m_fill);
            if (ret.length() < width)
                ret.append(m_fill);
        }
        return ret;
    }

    template<typename T>
    [[nodiscard]] std::string format(T const& arg) const
    {
        switch (m_type) {
        case FormatSpecifierType::Default:
        case FormatSpecifierType::String:
            return format_string(to_string<T>()(arg));
        case FormatSpecifierType::Int:
        case FormatSpecifierType::Character:
            return format_long(to_long<T>(arg));
        default:
            return format(to_double<T>(arg));
        }
    }

    [[nodiscard]] std::string format_string(std::string arg) const
    {
        auto ret = std::move(arg);
        if ((m_precision > 0) && (ret.length() > m_precision)) {
            ret = ret.substr(0, m_precision);
        }
        if (m_width > 0) {
            switch (m_alignment) {
            case FormatSpecifierAlignment::Left:
                ret = left_align(ret, m_width);
                break;
            case FormatSpecifierAlignment::Right:
                ret = right_align(ret, m_width);
                break;
            case FormatSpecifierAlignment::RightButSignLeft:
                fprintf(stderr, "= alignment specifier invalid for strings");
                exit(1);
            case FormatSpecifierAlignment::Center:
                ret = center(ret, m_width);
                break;
            }
        }
        return ret;
    }

    [[nodiscard]] std::string format_long(long arg) const
    {
        std::string sign;
        switch (m_display_sign) {
        case DisplaySign::OnlyForNegative:
            if (arg < 0)
                sign = "-";
            break;
        case DisplaySign::Always:
            sign = (arg < 0) ? "-" : "+";
            break;
        case DisplaySign::SpaceForPositive:
            sign = (arg < 0) ? "-" : " ";
            break;
        }
        if (arg < 0) {
            arg = -arg;
        }

        return format_integer(arg, sign);
    }

    [[nodiscard]] std::string format_integer(unsigned long integer, std::string const& sign) const
    {
        std::string ret;
        std::string s = sign;
        switch (m_type) {
        case FormatSpecifierType::Default:
        case FormatSpecifierType::Int:
        case FormatSpecifierType::LocaleAware:
            ret = render_integer(integer);
            break;
        case FormatSpecifierType::Character:
            s = "";
            ret += static_cast<char>(integer);
            break;
        default:
            fprintf(stderr, "format: %s: Type '%c' not allowed for integer values\n", m_specifier.c_str(), (char)m_type);
            exit(1);
        }
        if (m_width > 0) {
            switch (m_alignment) {
            case FormatSpecifierAlignment::Left:
                ret = left_align(sign + ret, m_width);
                break;
            case FormatSpecifierAlignment::Right:
                ret = right_align(sign + ret, m_width);
                break;
            case FormatSpecifierAlignment::RightButSignLeft:
                ret = right_align(sign + ret, m_width - sign.length());
                ret = sign + ret;
                break;
            case FormatSpecifierAlignment::Center:
                ret = center(sign + ret, m_width);
                break;
            }
        }
        switch (m_case_coercion) {
        case CaseCoercion::ToLower:
            std::transform(ret.begin(), ret.end(), ret.begin(),
                [](unsigned char c) { return std::tolower(c); });
            break;
        case CaseCoercion::ToUpper:
            std::transform(ret.begin(), ret.end(), ret.begin(),
                [](unsigned char c) { return std::tolower(c); });
            break;
        case CaseCoercion::DontCare:
            break;
        }
        return ret;
    }

    [[nodiscard]] std::string render_integer(unsigned long integer) const
    {
        if (integer == 0)
            return "0";
        std::string ret;
        while (integer > 0) {
            ret += "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[integer % m_base];
            integer /= m_base;
        }
        if (m_grouping_option != GroupingOption::None) {
            for (size_t ix = 3u; ix <= ret.length(); ix += 4) {
                ret.insert(ix, 1, static_cast<char>(m_grouping_option));
            }
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

    [[nodiscard]] std::string format_long(unsigned long arg) const
    {
        std::string sign;
        switch (m_display_sign) {
        case DisplaySign::OnlyForNegative:
            break;
        case DisplaySign::Always:
            sign = "+";
            break;
        case DisplaySign::SpaceForPositive:
            sign = " ";
            break;
        }
        return format_integer(arg, sign);
    }

    [[nodiscard]] std::string format_double(double arg) const
    {
        auto precision = m_precision;
        if (precision == 0)
            precision = 6;
        //        auto coercion = m_case_coercion;
        auto type = m_type;
        if (type == FormatSpecifierType::Default) {
            type = FormatSpecifierType::General;
            //            coercion = CaseCoercion::ToLower;
        }
        return std::to_string(arg);
    }

    static std::optional<FormatSpecifier> first_specifier(std::string const& msg, size_t offset = 0)
    {
        FormatState state = FormatState::String;
        std::string format_specifier;
        size_t start;
        std::string prefix;

        for (size_t ix = offset; ix < msg.length(); ix++) {
            auto ch = msg[ix];
            switch (state) {
            case FormatState::String:
                if (ch == '{') {
                    state = FormatState::FormatMaybe;
                    start = ix;
                } else {
                    prefix += ch;
                }
                break;
            case FormatState::FormatMaybe:
                if (ch == '{') {
                    state = FormatState::String;
                    prefix += ch;
                    start = -1;
                    break;
                }
                state = FormatState::Format;
                /* Fall through */
            case FormatState::Format:
                switch (ch) {
                case '\\':
                    state = FormatState::Escape;
                    break;
                case '}':
                    return FormatSpecifier(msg.substr(start, ix - start + 1), start, prefix);
                default:
                    break;
                }
                break;
            case FormatState::Escape:
                break;
            }
        }
        return {};
    }

    explicit FormatSpecifier(std::string const& specifier, size_t start, std::string prefix)
        : m_start(start)
        , m_length(specifier.length())
        , m_specifier(specifier)
        , m_prefix(std::move(prefix))
    {
        if (specifier.empty())
            return;

        StringBuffer buffer(specifier);
        if (!buffer.expect('{')) {
            fprintf(stderr, "Expected '{'\n");
            exit(1);
        }
        buffer.reset();
        if (buffer.is_one_of("<>=^", 1) != 0) {
            m_fill = buffer.read(1);
            buffer.reset();
        }
        if (auto alignment = buffer.one_of("<>=^"); alignment != 0) {
            m_alignment = (FormatSpecifierAlignment)alignment;
            buffer.reset();
        }
        if (auto display_sign = buffer.one_of(" +-"); display_sign != 0) {
            m_display_sign = (DisplaySign)display_sign;
            buffer.reset();
        }
        if (buffer.peek() == '#') {
            m_alternate = true;
            buffer.reset();
        }
        if (buffer.peek() == '0') {
            m_alignment = FormatSpecifierAlignment::RightButSignLeft;
            m_fill = "0";
            buffer.skip();
            buffer.reset();
        }

        auto read_number = [&buffer]() -> size_t {
            size_t ix = 0;
            while (isdigit(buffer.peek(ix)))
                ix++;
            if (ix > 0) {
                auto num = buffer.read(ix);
                buffer.reset();
                return to_long(num);
            }
            return 0;
        };

        m_width = read_number();
        if (auto grouping_option = buffer.one_of(",_"); grouping_option != 0) {
            m_grouping_option = (GroupingOption)grouping_option;
            buffer.reset();
        }
        if (buffer.peek() == '.') {
            buffer.skip();
            buffer.reset();
            m_precision = read_number();
            if (m_precision == 0) {
                fprintf(stderr, "Syntax error in format specifier: expected number following '.'\n");
                exit(1);
            }
        }

        switch (buffer.peek()) {
        case 's':
            m_type = FormatSpecifierType::String;
            break;

        case 'b':
            m_type = FormatSpecifierType::Int;
            m_base = 2;
            break;
        case 'c':
            m_type = FormatSpecifierType::Character;
            break;
        case 'd':
            m_type = FormatSpecifierType::Int;
            m_base = 10;
            break;
        case 'n':
            m_type = FormatSpecifierType::LocaleAware;
            break;
        case 'o':
            m_type = FormatSpecifierType::Int;
            m_base = 8;
            break;
        case 'X':
            m_type = FormatSpecifierType::Int;
            m_base = 16;
            m_case_coercion = CaseCoercion::ToUpper;
            break;
        case 'x':
            m_type = FormatSpecifierType::Int;
            m_base = 16;
            m_case_coercion = CaseCoercion::ToLower;
            break;

        case 'e':
            m_type = FormatSpecifierType::Scientific;
            m_case_coercion = CaseCoercion::ToLower;
            break;
        case 'E':
            m_type = FormatSpecifierType::Scientific;
            m_case_coercion = CaseCoercion::ToUpper;
            break;
        case 'f':
            m_type = FormatSpecifierType::FixedPoint;
            m_case_coercion = CaseCoercion::ToLower;
            break;
        case 'F':
            m_type = FormatSpecifierType::FixedPoint;
            m_case_coercion = CaseCoercion::ToUpper;
            break;
        case 'g':
            m_type = FormatSpecifierType::General;
            m_case_coercion = CaseCoercion::ToLower;
            break;
        case 'G':
            m_type = FormatSpecifierType::General;
            m_case_coercion = CaseCoercion::ToUpper;
            break;
        case '%':
            m_type = FormatSpecifierType::Percentage;
            break;

        default:
            m_type = FormatSpecifierType::Default;
            break;
        }
    }

    [[nodiscard]] std::string const& prefix() const { return m_prefix; }

private:
    FormatSpecifierType m_type { FormatSpecifierType::Default };
    size_t m_start { 0 };
    size_t m_length { 0 };
    int m_base { 10 };
    CaseCoercion m_case_coercion { CaseCoercion::DontCare };
    FormatSpecifierAlignment m_alignment = { FormatSpecifierAlignment::Left };
    std::string m_fill { " " };
    DisplaySign m_display_sign { DisplaySign::OnlyForNegative };
    bool m_alternate { false };
    GroupingOption m_grouping_option { GroupingOption::None };
    size_t m_width { 0 };
    size_t m_precision { 0 };
    //[[maybe_unused]] bool m_locale_aware { false };
    std::string m_specifier;
    std::string m_prefix;
};

static inline std::string format(std::string const& fmt)
{
    return fmt;
}

template<typename T>
std::pair<std::string,std::string> format_one(std::string const& fmt, T arg)
{
    std::optional<FormatSpecifier> specifier_maybe = FormatSpecifier::first_specifier(fmt);
    if (!specifier_maybe.has_value()) {
        auto a = to_string<T>()(arg);
        fprintf(stderr, "format(\"%s\", \"%s\", ...): Not enough format specifiers\n", fmt.c_str(), a.c_str());
        exit(1);
    }
    auto specifier = specifier_maybe.value();
    auto repl = specifier.format<T>(arg);
    return { specifier.prefix() + repl, fmt.substr(specifier.start() + specifier.length()) };
}

template<typename T, typename... Args>
std::string format(std::string const& fmt, T arg, Args&&... args)
{
    auto fmt_first_substituted = format_one<T>(fmt, arg);
    return fmt_first_substituted.first + format(fmt_first_substituted.second, std::forward<Args>(args)...);
}

template<typename... Args>
std::string format(char const* fmt, Args&&... args)
{
    return format(std::string(fmt), std::forward<Args>(args)...);
}

}
