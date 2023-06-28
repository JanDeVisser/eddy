/*
 * Copyright (c) 2022, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <filesystem>
#include <fstream>

#include <Core/Format.h>

#include <App/Document.h>
#include <App/Eddy.h>
#include <App/Editor.h>
//#include <Mode/CPlusPlus.h>
#include <Mode/Mode.h>
#include <Mode/PlainText.h>
//#include <Mode/Scribble.h>
#include <Widget/App.h>
#include <Widget/SDLContext.h>

using namespace Obelix;

namespace eddy {

FileType s_filetypes[] = {
    // Plain Text parser must be in slot 0! Do not sort down!
    { { ".txt" }, "text/plain", [](Document& doc) -> Mode* {
         return new PlainText(doc);
     } },
    /*
    { { ".cpp", ".h", ".hpp" }, "text/x-cpp", [](Document& doc) -> Mode* {
         return new CPlusPlus(doc);
     } },
    { { ".eddy" }, "text/x-eddy", []() -> EddyParser* {
         return new class ScribbleParser();
     } },
     */
};

FileType const& get_filetype(fs::path const& file)
{
    auto ext = file.extension();
    if (ext.empty())
        return s_filetypes[0];
    for (auto const& type : s_filetypes) {
        for (auto const& e : type.extensions) {
            if (e == ext)
                return type;
        }
    }
    return s_filetypes[0];
}

DocumentCommands::DocumentCommands()
{
    register_command(
        { "copy-to-clipboard", "Copy selection to clipboard", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.copy_to_clipboard();
            } },
        { SDLK_c, KMOD_CTRL });
    register_command(
        { "cut-to-clipboard", "Cut selection to clipboard", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.cut_to_clipboard();
            } },
        { SDLK_x, KMOD_CTRL });
    register_command(
        { "duplicate-line", "Duplicate current line", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.duplicate_line();
            } },
        { SDLK_d, KMOD_CTRL });
    register_command(
        { "find-first", "Find",
            { { "Find", CommandParameterType::String,
                []() -> std::string {
                    auto* doc = Eddy::editor()->document();
                    if (doc == nullptr)
                        return "";
                    return doc->selected_text();
                } } },
            [](Widget& w, strings const& args) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.find(args[0]);
            } },
        { SDLK_f, KMOD_CTRL });
    register_command(
        { "find-next", "Find next", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.find_next();
            } },
        { SDLK_f, KMOD_CTRL | KMOD_SHIFT });
    register_command(
        { "goto-line-column", "Goto line:column",
            { { "Line:Column to go to", CommandParameterType::String } },
            [](Widget& w, strings const& args) -> void {
                auto line_col = split(args[0], ':');
                if (line_col.empty())
                    return;
                if (auto line_maybe = try_to_long<std::string>()(line_col[0]); line_maybe.has_value()) {
                    auto& doc = dynamic_cast<Document&>(w);
                    auto col = doc.point_column();
                    if (line_col.size() > 1) {
                        if (auto col_maybe = try_to_long<std::string>()(line_col[1]); col_maybe.has_value())
                            col = col_maybe.value();
                    }
                    doc.move_to(line_maybe.value() - 1, col - 1, false);
                }
            } },
        { SDLK_g, KMOD_CTRL });
    register_command(
        { "paste-from-clipboard", "Paste text from clipboard", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.paste_from_clipboard();
            } },
        { SDLK_v, KMOD_CTRL });
    register_command(
        { "redo", "Redo edit", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.redo();
            } },
        { SDLK_y, KMOD_CTRL });
    register_command(
        { "save-current-as", "Save current file as",
            { { "New file name", CommandParameterType::String } },
            [](Widget& w, strings const& args) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.save_as(args[0]);
            } },
        { SDLK_s, KMOD_CTRL | KMOD_GUI });
    register_command(
        { "save-file", "Save current file", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                if (doc.path().empty()) {
                    App::instance().schedule(doc.command("save-current-as").value());
                } else {
                    doc.save();
                }
            } },
        { SDLK_s, KMOD_CTRL });
    register_command(
        { "select-all", "Select all", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.select_all();
            } },
        { SDLK_a, KMOD_CTRL });
    register_command(
        { "select-line", "Select line", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.select_line();
            } });
    register_command(
        { "select-word", "Select word", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.select_word();
            } },
        { SDLK_UP, KMOD_GUI });
    register_command(
        { "transpose-lines-down", "Transpose lines down", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.transpose_lines(Document::TransposeDirection::Down);
            } },
        { SDLK_DOWN, KMOD_ALT });
    register_command(
        { "transpose-lines-up", "Transpose lines up", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.transpose_lines(Document::TransposeDirection::Up);
            } },
        { SDLK_UP, KMOD_ALT });
    register_command(
        { "undo", "Undo edit", {},
            [](Widget& w, strings const&) -> void {
                auto& doc = dynamic_cast<Document&>(w);
                doc.undo();
            } },
        { SDLK_z, KMOD_CTRL });
}

DocumentCommands Document::s_document_commands;

Document::Document(Editor* editor)
    : Buffer(editor)
{
    m_path.clear();
    m_filetype = get_filetype("");
    m_mode = std::unique_ptr<Mode>(m_filetype.mode_builder(*this));
    m_commands = &s_document_commands;
}

Line const& Document::line(size_t line_no)
{
    assert(line_no < m_text.size());
    return m_text[line_no];
}

void Document::fill_lines()
{
    PlainTextParser parser;
    m_text.parse(parser);
}

fs::path const& Document::path() const
{
    return m_path;
}

std::string Document::title() const
{
    return m_path;
}

std::string Document::short_title() const
{
    return fs::relative(path()).string();
}

std::string Document::status() const
{
    std::stringstream ss;
    ss << point_line() + 1 << ":" << point_column() + 1 << " [";
    ss << screen_top() + 1 << ":" << screen_left() + 1 << "]";
    return ss.str();
}

size_t Document::text_length() const
{
    return m_text.length();
}

size_t Document::line_length(size_t line_no) const
{
    return m_text.line_length(line_no);
}

size_t Document::line_count() const
{
    return m_text.size();
}

bool Document::empty() const
{
    return m_text.empty() || (m_text.length() == 0);
}

void Document::split_line()
{
    insert("\n");
}

void Document::join_lines()
{
    auto line = m_text.find_line_number(m_point);
    if (line < (line_count() - 1)) {
        m_point = m_text[line].end_index();
        m_text.join_lines(line);
        update_internals(false);
    }
}

void Document::duplicate_line()
{
    auto point = m_point;
    auto line = m_text.find_line_number(m_point);
    auto len = line_length(line);
    m_text.duplicate_line(line);
    move_point(point + len + 1);
    m_mark = m_point;
    update_internals(false);
}

void Document::transpose_lines(TransposeDirection direction)
{
    if (line_count() < 2)
        return;
    auto line = m_text.find_line_number(m_point);
    auto column = m_point - m_text.index_of(line);
    if (((direction == TransposeDirection::Down) && (line < line_count() - 1)) || ((direction == TransposeDirection::Up) && (line > 0))) {
        auto top_line = (direction == TransposeDirection::Down) ? line : line - 1;
        auto offset = (direction == TransposeDirection::Down) ? line_length(top_line) + 1 + column : column;
        m_text.transpose_lines(top_line);
        move_point(m_text.index_of(top_line) + offset);
        update_internals(false);
    }
}

void Document::insert_text(std::string const& str, std::optional<size_t> point)
{
    if (str.empty())
        return;
    auto p = (point.has_value()) ? point.value() : m_point;
    m_text.insert(p, str);
    m_changed = true;
    m_point += static_cast<size_t>(str.length());
}

void Document::insert(std::string const& str)
{
    if (str.empty())
        return;
    erase_selection();
    insert_text(str);
    add_edit_action(EditAction::insert_text(m_point - static_cast<size_t>(str.length()), str));
    update_internals(false);
}

void Document::reset_selection()
{
    m_mark = m_point;
}

void Document::extend_selection(int num)
{
    auto point = m_point;
    auto& left = (m_mark <= m_point) ? m_mark : m_point;
    auto& right = (m_mark <= m_point) ? m_point : m_mark;

    if (num < 0) {
        left -= std::min(static_cast<size_t>(-num), left);
    } else {
        right += std::min(static_cast<size_t>(num), text_length() - right);
    }
    add_edit_action(EditAction::move_cursor(point, m_point));
}

void Document::select_word()
{
    auto point = m_point;
    m_point = static_cast<size_t>(m_text.word_boundary_left(point));
    m_mark = static_cast<size_t>(m_text.word_boundary_right(point));
    add_edit_action(EditAction::move_cursor(point, m_point));
}

void Document::select_line()
{
    auto line = m_text.find_line_number(m_point);
    move_point(static_cast<size_t>(m_text.index_of(line)));
    if (line < m_text.size() - 1)
        m_mark = m_text.index_of(line + 1);
    else
        m_mark = text_length();
}

void Document::select_all()
{
    m_mark = 0;
    move_point(text_length());
}

std::string Document::selected_text()
{
    if (m_point == m_mark)
        return "";
    size_t start_selection = std::min(m_point, m_mark);
    size_t end_selection = std::max(m_point, m_mark);
    return m_text.substring(start_selection, end_selection - start_selection);
}

void Document::erase(size_t point, size_t len)
{
    m_text.remove(point, len);
    m_mark = m_point = point;
}

void Document::erase_selection()
{
    if (m_point == m_mark)
        return;
    size_t start_selection = std::min(m_point, m_mark);
    size_t end_selection = std::max(m_point, m_mark);
    add_edit_action(EditAction::delete_text(start_selection, m_text.substring(start_selection, end_selection - start_selection)));
    erase(start_selection, end_selection - start_selection);
    move_point(start_selection);
    update_internals(false);
}

void Document::copy_to_clipboard()
{
    if (m_point == m_mark) {
        home(false);
        end(true);
    }
    auto selection = selected_text();
    if (!selection.empty()) {
        if (auto err = SDL_SetClipboardText(selection.c_str()); err != 0) {
            fatal("Error copying selection to clipboard: {}", SDL_GetError());
        }
    }
}

void Document::cut_to_clipboard()
{
    copy_to_clipboard();
    erase_selection();
}

void Document::paste_from_clipboard()
{
    if (SDL_HasClipboardText() == SDL_FALSE)
        return;
    if (auto clipboard = SDL_GetClipboardText(); (clipboard != nullptr) && clipboard[0])
        insert(clipboard);
}

DocumentPosition Document::position(size_t cursor) const
{
    auto line = m_text.find_line_number(cursor);
    if (line < line_count())
        return { line, cursor - m_text.index_of(line) };
    else
        return { line_count(), 0 };
}

size_t Document::position_to_cursor(DocumentPosition position) {
    if (line_count() == 0) {
        return 0;
    }
    position.line = clamp(position.line, 0ul, line_count() - 1);
    position.column = clamp(position.column, 0ul, line_length(position.line));
    return m_text.index_of(position.line) + position.column;
}

size_t Document::point_line() const
{
    return m_text.find_line_number(m_point);
}

size_t Document::point_column() const
{
    auto pos = position(m_point);
    return pos.column;
}

size_t Document::mark_line() const
{
    return m_text.find_line_number(m_mark);
}

size_t Document::mark_column() const
{
    auto pos = position(m_mark);
    return pos.column;
}

void Document::set_point_and_mark(size_t point, std::optional<size_t> mark)
{
    auto m = mark.value_or(point);
    m_point = point;
    m_mark = m;
    auto line = m_text.find_line_number(m_point);
    auto column = m_point - m_text.index_of(line);
    if (m_screen_top > line || m_screen_top + rows() < line)
        m_screen_top = line - rows() / 2;
    if (m_screen_left > column || m_screen_left + columns() < column)
        m_screen_left = column - columns() / 2;
    update_internals(mark != point, line);
}

void Document::move_to(size_t line, size_t column, bool select)
{
    if (line_count() == 0) {
        line = 0;
        column = 0;
    } else {
        line = clamp(line, 0ul, line_count() - 1);
        column = clamp(column, 0ul, line_length(line));
    }
    move_point(position_to_cursor(DocumentPosition { line, column }));
    if (m_screen_top > line || m_screen_top + rows() < line)
        m_screen_top = line - rows() / 2;
    if (m_screen_left > column || m_screen_left + columns() < column)
        m_screen_left = column - columns() / 2;
    update_internals(select, line);
}

void Document::update_internals(bool select, size_t line)
{
    if (m_changed) {
        fill_lines();
        m_changed = false;
    }
    auto pos = position(m_point);
    line = pos.line;
    auto column = pos.column;
    m_screen_top = clamp(m_screen_top, better_max(0ul, line - editor()->rows() + 1), line);
    m_screen_left = clamp(m_screen_left, better_max(0ul, column - editor()->columns() + 1), column);
    if (!select)
        m_mark = m_point;
}

void Document::move_point(size_t point)
{
    if (point == m_point)
        return;
    add_edit_action(EditAction::move_cursor(m_point, point));
    m_point = point;
}

void Document::add_edit_action(EditAction action)
{
    m_mode->on_change(action);
    auto undo_pointer = m_undo_pointer.value_or(0ul);
    if (undo_pointer < m_edits.size() - 1) {
        m_edits.erase(
            m_edits.begin() + static_cast<int>(clamp(undo_pointer, 0ul, m_edits.size() - 1)),
            m_edits.end());
    }
    if (!m_edits.empty()) {
        if (auto merged = m_edits.back().merge(action); merged.has_value()) {
            m_edits.pop_back();
            m_edits.push_back(merged.value());
            m_undo_pointer = m_edits.size() - 1;
            return;
        }
    }
    m_edits.push_back(std::move(action));
    m_undo_pointer = m_edits.size() - 1;
}

void Document::undo()
{
    if (!m_edits.empty() && m_undo_pointer.has_value() && (m_undo_pointer.value() < m_edits.size())) {
        auto undo_pointer = m_undo_pointer.value();
        m_edits[undo_pointer].undo(*this);
        if (undo_pointer > 0) {
            m_undo_pointer = undo_pointer - 1;
        } else {
            m_undo_pointer.reset();
        }
    }
}

void Document::redo()
{
    if (!m_edits.empty() && m_undo_pointer.has_value() && (m_undo_pointer.value() < m_edits.size())) {
        m_edits[m_undo_pointer.value()].undo(*this);
        m_undo_pointer = m_undo_pointer.value() + 1;
    }
}

void Document::up(bool select)
{
    size_t line = point_line();
    size_t column = point_column();
    if (line > 0) {
        move_point(position_to_cursor(DocumentPosition { line - 1, column }));
        update_internals(select, line - 1);
    }
}

void Document::down(bool select)
{
    size_t line = point_line();
    size_t column = point_column();
    if (line < (line_count() - 1)) {
        move_point(position_to_cursor(DocumentPosition { line + 1, column }));
        update_internals(select, line + 1);
    }
}

void Document::left(bool select)
{
    if (m_point > 0)
        move_point(m_point - 1);
    update_internals(select);
}

void Document::word_left(bool select)
{
    auto point = m_point;
    while (0 < point && !isalnum(m_text.char_at(point))) {
        --point;
    }
    while (0 < point && isalnum(m_text.char_at(point))) {
        --point;
    }
    move_point(point);
    update_internals(select);
}

void Document::right(bool select)
{
    if (m_point < text_length() - 1)
        move_point(m_point + 1);
    update_internals(select);
}

void Document::word_right(bool select)
{
    auto point = m_point;
    while (point < text_length() - 1 && !isalnum(m_text.char_at(point))) {
        ++point;
    }
    while (point < text_length() - 1 && isalnum(m_text.char_at(point))) {
        ++point;
    }
    move_point(point);
    update_internals(select);
}

void Document::page_up(bool select)
{
    auto line = m_text.find_line_number(m_point);
    auto column = m_point - m_text[line].index();
    line = clamp(line - rows(), 0ul, line);
    column = clamp(column, 0ul, line_length(line));
    move_point(m_text[line].index() + column);
    update_internals(select, line);
}

void Document::page_down(bool select)
{
    auto line = m_text.find_line_number(m_point);
    size_t column = m_point - m_text[line].index();
    line = clamp(line + rows(), line, line_count() - 1);
    column = clamp(column, 0ul, line_length(line));
    move_point(m_text[line].index() + column);
    update_internals(select, line);
}

void Document::home(bool select)
{
    auto line = m_text.find_line_number(m_point);
    auto home = m_text.index_of(line);
    move_point(home);
    update_internals(select);
}

void Document::end(bool select)
{
    auto line = m_text.find_line_number(m_point);
    auto end = m_text.index_of_end(line);
    move_point(end);
    update_internals(select);
}

void Document::top(bool select)
{
    move_to(0, 0, select);
}

void Document::bottom(bool select)
{
    move_to(line_count() - 1, line_length(line_count() - 1), select);
}

bool Document::find(std::string const& term)
{
    m_found = true;
    m_find_term = term;
    return find_next();
}

bool Document::find_next()
{
    if (m_find_term.empty())
        return true;
    auto stash_point = m_point;
    auto stash_mark = m_mark;
    if (!m_found) {
        m_mark = m_point = 0;
    }
    auto where = m_text.find(m_find_term, m_point);
    if (where.has_value()) {
        m_mark = where.value();
        move_point(m_mark + m_find_term.length());
        m_found = true;
        update_internals(true);
        return true;
    }
    m_point = stash_point;
    m_mark = stash_mark;
    update_internals(true);
    m_found = false;
    return false;
}

void Document::clear()
{
    m_text.remove_all();
    update_internals(false);
}

std::optional<std::string> Document::load(std::string const& file_name)
{
    m_path = fs::absolute(file_name);
    m_filetype = get_filetype(m_path);
    m_mode = std::unique_ptr<Mode>(m_filetype.mode_builder(*this));

    auto text_maybe = m_mode->open_file(m_path);
    if (text_maybe.is_error())
        return text_maybe.error().to_string();
    m_text.assign(text_maybe.value());
    m_mode->on_load();
    m_point = m_mark = 0;
    m_dirty = false;
    fill_lines();
    m_changed = false;
    return {};
}

std::optional<std::string> Document::save()
{
    if (!m_dirty)
        return {};
    std::fstream s(m_path.string(), std::fstream::out);
    if (!s.is_open())
        return format("Error opening '{}'", m_path.string());
    s << m_text.text();
    if (s.fail() || s.bad())
        return format("Error saving '{}'", m_path.string());
    m_dirty = false;
    return {};
}

std::optional<std::string> Document::save_as(std::string const& new_file_name)
{
    m_path = new_file_name;
    m_filetype = get_filetype(m_path);
    m_mode = std::unique_ptr<Mode>(m_filetype.mode_builder(*this));
    return save();
}

void Document::render()
{
    auto point_line = m_text.find_line_number(m_point);
    auto point_column = (point_line < line_count()) ? m_point - m_text[point_line].index() : 0;
    editor()->mark_current_line(point_line - m_screen_top);

    bool has_selection = m_point != m_mark;
    size_t start_selection = std::min(m_point, m_mark);
    size_t end_selection = std::max(m_point, m_mark);
    for (auto ix = m_screen_top; ix < std::min(line_count(), m_screen_top + editor()->rows()); ++ix) {
        auto const& line = m_text[ix];
        auto line_len = line_length(ix);
        auto line_end = line.index() + line_len;
        if (has_selection && (start_selection <= line_end) && (end_selection >= line.index())) {
            size_t start_block = start_selection - line.index();
            if (line.index() > start_selection)
                start_block = 0;
            size_t end_block = end_selection - line.index();
            if (end_block > line_len)
                end_block = editor()->columns();
            size_t block_width = end_block - start_block;
            if (block_width > 0) {
                editor()->box(
                    start_block * App::instance().context()->character_width(),
                    editor()->line_top(ix - m_screen_top),
                    block_width * App::instance().context()->character_width(),
                    editor()->line_height(),
                    Eddy::eddy().color(PaletteIndex::Selection)
                );
            }
        }

        auto len = 0u;
        for (auto const& token : line.tokens()) {
            auto t = token.text;
            if (len + t.length() < static_cast<size_t>(m_screen_left)) {
                len += t.length();
                continue;
            } else if (len < static_cast<size_t>(m_screen_left)) {
                t = t.substr(m_screen_left - len);
            } else if (len + t.length() > static_cast<size_t>(m_screen_left + columns())) {
                t = t.substr(0, m_screen_left + columns() - len);
            }
            editor()->append(DisplayToken { t, token.color });
            len += token.text.length();
            if (len >= static_cast<size_t>(m_screen_left + editor()->columns()))
                break;
        }
        editor()->newline();
    }

    editor()->text_cursor(point_line - m_screen_top, point_column - m_screen_left);
}

bool Document::dispatch(SDL_Keysym sym)
{
    switch (sym.sym) {
    case SDLK_ESCAPE:
        m_mark = m_point;
        break;
    case SDLK_UP:
        up(sym.mod & KMOD_SHIFT);
        break;
    case SDLK_PAGEUP:
        page_up(sym.mod & KMOD_SHIFT);
        break;
    case SDLK_DOWN:
        down(sym.mod & KMOD_SHIFT);
        break;
    case SDLK_PAGEDOWN:
        page_down(sym.mod & KMOD_SHIFT);
        break;
    case SDLK_LEFT:
        if (sym.mod & KMOD_GUI)
            word_left(sym.mod & KMOD_SHIFT);
        else
            left(sym.mod & KMOD_SHIFT);
        break;
    case SDLK_RIGHT:
        if (sym.mod & KMOD_GUI)
            word_right(sym.mod & KMOD_SHIFT);
        else
            right(sym.mod & KMOD_SHIFT);
        break;
    case SDLK_HOME:
        if (sym.mod & KMOD_GUI) {
            move_to(0, 0, sym.mod & KMOD_SHIFT);
        } else {
            home(sym.mod & KMOD_SHIFT);
        }
        break;
    case SDLK_END:
        if (sym.mod & KMOD_GUI) {
            move_to(line_count() - 1, line_length(line_count() - 1), sym.mod & KMOD_SHIFT);
        } else {
            end(sym.mod & KMOD_SHIFT);
        }
        break;
    case SDLK_BACKSPACE:
    case SDLK_DELETE:
        if (m_point == m_mark)
            extend_selection((sym.sym == SDLK_BACKSPACE) ? -1 : 1);
        erase_selection();
        break;
    case SDLK_RETURN:
    case SDLK_KP_ENTER:
        split_line();
        break;
    default:
        return false;
    }
    return true;
}

void Document::mousedown(Position mouse)
{
    move_to(m_screen_top + mouse.line(), m_screen_left + mouse.column(), false);
}

void Document::motion(Position mouse)
{
    move_to(m_screen_top + mouse.line(), m_screen_left + mouse.column(), true);
}

void Document::click(Position mouse, int clicks)
{
    switch (clicks) {
    case 2:
        select_word();
        break;
    case 3:
        select_line();
        break;
    default:
        break;
    }
}

void Document::wheel(int lines)
{
    if (lines >= 0)
        m_screen_top = clamp(m_screen_top + lines, 0ul, line_count() - 1);
    else
        m_screen_top = clamp(static_cast<int>(m_screen_top) + lines, 0ul, line_count() - 1);
}

void Document::handle_text_input()
{
    insert(App::instance().input_buffer());
}

std::optional<ScheduledCommand> Document::command(std::string const& name) const
{
    if (auto ret = Widget::command(name); ret.has_value())
        return ret;
    if (m_mode != nullptr) {
        if (auto ret = m_mode->command(name); ret.has_value())
            return ret;
    }
    return {};
}

std::vector<ScheduledCommand> Document::commands() const
{
    auto ret = Widget::commands();
    if (m_mode != nullptr) {
        for (auto const& cmd : m_mode->commands())
            ret.push_back({ const_cast<Document&>(*this), cmd });
    }
    return ret;
}

}
