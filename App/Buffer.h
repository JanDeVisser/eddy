/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <numeric>

#include <App/EditorState.h>
#include <Lexer/Token.h>
#include <Widget/Widget.h>

using namespace Obelix;

namespace eddy {

struct DocumentPosition {
    size_t line { 0 };
    size_t column { 0 };

    void clear()
    {
        line = column = 0;
    }
    auto operator<=>(DocumentPosition const& other) const = default;
};

class LineToken {
public:
    LineToken(size_t index, std::string_view text, PaletteIndex color)
        : m_index(index)
        , m_token(text, color)
    {
    }

    [[nodiscard]] size_t index() const
    {
        return m_index;
    }

    [[nodiscard]] size_t end_index() const
    {
        return m_index + m_token.text.length();
    }

    [[nodiscard]] DisplayToken const& token() const
    {
        return m_token;
    }

private:
    size_t m_index;
    DisplayToken m_token;
};

PaletteIndex color_for(TokenCode code);

class Line : public std::vector<LineToken> {
public:
    explicit Line(class Text& text, size_t start_index);
    [[nodiscard]] size_t index() const;
    [[nodiscard]] size_t end_index() const;
    [[nodiscard]] size_t length() const;
    [[nodiscard]] std::string_view text() const;
    [[nodiscard]] std::vector<DisplayToken> tokens() const;

private:
    Text& m_text;
    size_t m_start_index { 0 };
    std::vector<LineToken> m_tokens {};
};

class Text : public std::vector<Line> {
public:
    Text();
    [[nodiscard]] std::string_view text() const;
    [[nodiscard]] size_t length() const;
    [[nodiscard]] char char_at(size_t) const;
    [[nodiscard]] size_t line_length(size_t line) const;
    [[nodiscard]] size_t index_of(size_t line) const;
    [[nodiscard]] size_t index_of_end(size_t line) const;

    // Navigation functions
    [[nodiscard]] size_t find_line_number(size_t offset) const;
    [[nodiscard]] size_t word_boundary_left(size_t index) const;
    [[nodiscard]] size_t word_boundary_right(size_t index) const;
    [[nodiscard]] std::string substring(size_t from, size_t length) const;
    [[nodiscard]] std::optional<size_t> find(std::string const& find_term, size_t offset) const;

    // Edit functions
    void insert(size_t at, std::string const& str);
    void insert(size_t at, std::string_view str);
    void remove(size_t at, size_t num);
    void remove_all();
    void join_lines(size_t first_line);
    void duplicate_line(size_t line);
    void transpose_lines(size_t first_line);
    void assign(std::string const&);

    template <class Parser>
    void parse(Parser& parser)
    {
        std::lock_guard const lock { m_lock };
        if (!m_dirty)
            return;
        parser.assign(std::string_view(m_text));
        clear();
        emplace_back(*this, 0);
        for (Token token = parser.lex(); token.code() != TokenCode::EndOfFile; token = parser.lex()) {
            size_t length = token.length();
            switch (token.code()) {
            case TokenCode::NewLine:
                m_offset += length;
                emplace_back(*this, m_offset);
                break;
            default:
                PaletteIndex color = color_for(token.code());
                back().emplace_back(m_offset, std::string_view(m_text).substr(m_offset, length), color);
                m_offset += length;
                break;
            }
        }
        m_dirty = false;
    }

private:
    friend class Line;
    std::string m_text;
    bool m_dirty { false };
    size_t m_offset { 0 };
    std::recursive_mutex m_lock;
};

class Buffer : public Widget {
public:
    [[nodiscard]] int rows() const;
    [[nodiscard]] int columns() const;
    [[nodiscard]] virtual std::string title() const = 0;
    [[nodiscard]] virtual std::string short_title() const;
    [[nodiscard]] virtual std::string status() const = 0;
    virtual void on_activate() {};
    virtual void on_deactivate() {};
    virtual void mousedown(Position) {};
    virtual void motion(Position) {};
    virtual void click(Position, int) {};
    virtual void wheel(int) {};

protected:
    explicit Buffer(Editor*);
    [[nodiscard]] Editor* editor() { return m_editor; }

private:
    Editor* m_editor;
};

} // Eddy
