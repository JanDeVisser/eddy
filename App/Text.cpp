/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <App/Text.h>

namespace eddy {

Line::Line(Text& text, size_t start_index, int start_level)
    : std::vector<LineToken>()
    , m_text(text)
    , m_start_index(start_index)
    , m_start_level(start_level)
    , m_end_level(start_level)
{
}

size_t Line::index() const
{
    return m_start_index;
}

size_t Line::end_index() const
{
    return (empty()) ? 0 : back().end_index();
}

size_t Line::length() const
{
    return end_index() - index();
}

std::string_view Line::text() const
{
    return std::string_view(m_text.m_text).substr(m_start_index, length());
}

std::vector<DisplayToken> Line::tokens() const
{
    std::vector<DisplayToken> ret;
    for (auto const& t : *this)
        ret.emplace_back(t.token()); // NOLINT(performance-inefficient-vector-operation)
    return ret;
}

Text::Text()
    : std::vector<Line>()
{
    emplace_back(*this, 0, 0);
}

std::string_view Text::text() const
{
    return std::string_view(m_text);
}

size_t Text::length() const
{
    return (empty()) ? 0 : back().end_index();
}

char Text::char_at(size_t ix) const
{
    assert(ix < m_text.length());
    return m_text[ix];
}

size_t Text::line_length(size_t line) const
{
    assert(line < size());
    return at(line).length();
}

size_t Text::index_of(size_t line) const
{
    assert(line < size());
    return at(line).index();
}

size_t Text::index_of_end(size_t line) const
{
    assert(line < size());
    return at(line).end_index();
}

size_t Text::find_line_number(size_t offset) const
{
    if (empty()) {
        return 0;
    }
    size_t line_min = 0;
    size_t line_max = size() - 1;
    while (true) {
        size_t line = line_min + (line_max - line_min) / 2;
        if ((line < size() - 1 && at(line).index() <= offset && offset < at(line + 1).index()) || (line == size() - 1 && at(line).index() <= offset)) {
            return line;
        } else {
            if (at(line).index() > offset) {
                line_max = line;
            } else {
                line_min = line + 1;
            }
        }
    }
}

size_t Text::word_boundary_left(size_t index) const
{
    if (isalnum(m_text[index]) || m_text[index] == '_') {
        while (index > 0 && (isalnum(m_text[index - 1]) || m_text[index - 1] == '_'))
            --index;
    } else {
        while (index > 0 && (!isalnum(m_text[index - 1]) && m_text[index - 1] != '_'))
            --index;
    }
    return index;
}

size_t Text::word_boundary_right(size_t index) const
{
    auto max_index = length() - 1;
    if (isalnum(m_text[index]) || m_text[index] == '_') {
        while (index < max_index && (isalnum(m_text[index + 1]) || m_text[index + 1] == '_'))
            ++index;
    } else {
        while (index < max_index && !isalnum(m_text[index + 1] && m_text[index + 1] != '_'))
            ++index;
    }
    return index;
}

std::string Text::substring(size_t from, size_t length) const
{
    return std::string(m_text.substr(from, length));
}

std::optional<size_t> Text::find(std::string const& find_term, size_t offset) const
{
    auto ret = m_text.find(find_term, offset);
    if (ret == std::string::npos)
        return {};
    return ret;
}

void Text::insert(size_t at, std::string const& str)
{
    std::lock_guard const lock { m_lock };
    m_text.insert(at, str);
    m_dirty = true;
}

void Text::insert(size_t at, std::string_view str)
{
    std::lock_guard const lock { m_lock };
    m_text.insert(at, str);
    m_dirty = true;
}

void Text::remove(size_t at, size_t num)
{
    std::lock_guard const lock { m_lock };
    m_text.erase(at, num);
    m_dirty = true;
}

void Text::join_lines(size_t first_line)
{
    if (first_line >= size() - 1)
        return;
    auto ix = at(first_line).end_index();
    assert(m_text[ix] == '\n');
    remove(ix, 1);
}

void Text::duplicate_line(size_t line)
{
    if (line >= size())
        return;
    auto len = at(line).length();
    insert(at(line).end_index(), "\n" + m_text.substr(at(line).index(), len));
}

void Text::transpose_lines(size_t first_line)
{
    if ((size() < 2) || (first_line > size() - 2))
        return;
    auto index_1 = at(first_line).index();
    auto len_1 = at(first_line).length();
    auto len_2 = at(first_line + 1).length();
    auto first = m_text.substr(index_1, len_1);
    auto second = m_text.substr(at(first_line + 1).index(), len_2);
    remove(index_1, len_1 + len_2 + 1);
    insert(index_1, first + "\n" + second);
}

void Text::remove_all()
{
    remove(0, length());
}

void Text::assign(std::string const& txt)
{
    clear();
    m_text = txt;
    m_dirty = true;
}

}
