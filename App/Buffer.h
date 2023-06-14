/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <numeric>

#include <lexer/Token.h>
#include <App/EditorState.h>
#include <Widget/Widget.h>

namespace scratch {

class Line {
public:
    Line() = default;
    Line(size_t index, std::string_view text)
        : m_start_index(index)
        , m_text(text)
    {
    }

    [[nodiscard]] size_t index() const
    {
        return m_start_index;
    }

    [[nodiscard]] std::string_view const& text() const {
        return m_text;
    }

    [[nodiscard]] size_t length() const
    {
        return m_text.length();
    }

    void clear()
    {
        m_tokens.clear();
    }

    void add_token(size_t length, PaletteIndex color)
    {
        auto offset { 0u };
        if (!m_tokens.empty()) {
            auto last = m_tokens.back();
            offset = last.offset + last.token.text.length();
        }
        if (offset + length <= m_text.length())
            m_tokens.emplace_back(offset, m_text.substr(offset, length), color);
    }

    [[nodiscard]] std::vector<DisplayToken> tokens() const
    {
        if (m_tokens.empty())
            return { DisplayToken { m_text, PaletteIndex::Default } };

        std::vector<DisplayToken> ret;
        for (auto const& t : m_tokens)
            ret.emplace_back(t.token); // NOLINT(performance-inefficient-vector-operation)
        return ret;
    }

private:
    struct LineToken {
        LineToken(size_t start, std::string_view text, PaletteIndex color)
            : offset(start)
            , token(text, color)
        {
        }

        size_t offset;
        DisplayToken token;
    };

    size_t m_start_index {0};
    std::string_view m_text;
    std::vector<LineToken> m_tokens {};
};

struct DocumentPosition {
    int line { 0 };
    int column { 0 };

    void clear()
    {
        line = column = 0;
    }
    auto operator<=>(DocumentPosition const& other) const = default;
};

class Buffer : public Widget {
public:
    [[nodiscard]] int rows() const;
    [[nodiscard]] int columns() const;
    [[nodiscard]] virtual std::string title() const = 0;
    [[nodiscard]] virtual std::string short_title() const;
    [[nodiscard]] virtual std::string status() const = 0;
    virtual void on_activate() { };
    virtual void on_deactivate() { };
    virtual void mousedown(int, int) { };
    virtual void motion(int, int) { };
    virtual void click(int, int, int) { };
    virtual void wheel(int) { };
protected:
    explicit Buffer(Editor*);
    [[nodiscard]] Editor* editor() { return m_editor; }
private:
    Editor* m_editor;
};

} // Scratch
