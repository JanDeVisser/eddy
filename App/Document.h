/*
 * Copyright (c) 2022, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <deque>
#include <filesystem>

#include <SDL.h>

#include <App/Buffer.h>
#include <App/Text.h>
#include <Widget/Command.h>
#include <Widget/Widget.h>

namespace eddy {

namespace fs=std::filesystem;

using namespace Obelix;

class Mode;

struct FileType {
    std::vector<std::string> extensions;
    std::string mimetype;
    std::function<Mode*(Document&)> mode_builder;
};

enum class EditActionType {
    InsertText,
    DeleteText,
    CursorMove,
};

struct DocumentCommands : public Commands {
    DocumentCommands();
};

class EditAction {
public:
    static EditAction insert_text(size_t, std::string);
    static EditAction delete_text(size_t, std::string);
    static EditAction move_cursor(size_t, size_t);

    [[nodiscard]] size_t cursor() const { return m_cursor; }
    [[nodiscard]] EditActionType type() const { return m_type; }
    [[nodiscard]] std::string const& text() const { return m_text; }
    [[nodiscard]] size_t pointer() const { return m_pointer; }

    void undo(Document&) const;
    void redo(Document&) const;
    [[nodiscard]] std::optional<EditAction> merge(EditAction const&) const;
private:
    EditAction(EditActionType, size_t, std::string);
    EditAction(EditActionType, size_t, size_t);
    EditActionType m_type;
    size_t m_cursor {0};
    size_t m_pointer {0};
    std::string m_text;
};

class Document : public Buffer {
public:
    explicit Document(Editor *);

    [[nodiscard]] size_t text_length() const;
    [[nodiscard]] Line const& line(size_t);
    [[nodiscard]] std::string_view text() const { return m_text.text(); }
    [[nodiscard]] size_t line_length(size_t) const;
    [[nodiscard]] size_t line_count() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] fs::path const& path() const;
    [[nodiscard]] std::string title() const override;
    [[nodiscard]] std::string short_title() const override;
    [[nodiscard]] std::string status() const override;

    [[nodiscard]] size_t screen_top() const { return m_screen_top; }
    [[nodiscard]] size_t screen_left() const { return m_screen_left; }

    [[nodiscard]] DocumentPosition position(size_t) const;
    [[nodiscard]] size_t position_to_cursor(DocumentPosition);
    [[nodiscard]] size_t point() const { return m_point; };
    [[nodiscard]] size_t mark() const { return m_mark; }
    [[nodiscard]] size_t point_line() const;
    [[nodiscard]] size_t point_column() const;
    [[nodiscard]] size_t mark_line() const;
    [[nodiscard]] size_t mark_column() const;

    void undo();
    void redo();

    void split_line();
    void insert(std::string const&);
    void join_lines();
    void duplicate_line();

    enum class TransposeDirection {
        Up,
        Down,
    };
    void transpose_lines(TransposeDirection direction = TransposeDirection::Down);

    void reset_selection();
    void extend_selection(int num);
    void select_word();
    void select_line();
    void select_all();
    std::string selected_text();
    void erase_selection();
    void copy_to_clipboard();
    void cut_to_clipboard();
    void paste_from_clipboard();

    void move_to(size_t, size_t, bool);
    void up(bool);
    void down(bool);
    void left(bool);
    void word_left(bool);
    void right(bool);
    void word_right(bool);
    void page_up(bool);
    void page_down(bool);
    void home(bool);
    void end(bool);
    void top(bool);
    void bottom(bool);

    bool find(std::string const&);
    bool find_next();

    void clear();
    std::optional<std::string> load(std::string const&);
    std::optional<std::string> save();
    std::optional<std::string> save_as(std::string const&);
    [[nodiscard]] bool dirty() const { return m_dirty; }

    void render() override;
    bool dispatch(SDL_Keysym) override;
    void mousedown(Position mouse) override;
    void motion(Position mouse) override;
    void click(Position mouse, int clicks) override;
    void wheel(int) override;
    void handle_text_input() override;

    [[nodiscard]] auto last_parse_time() const { return m_last_parse_time.count(); }

    std::optional<ScheduledCommand> command(std::string const&) const override;
    [[nodiscard]] std::vector<ScheduledCommand> commands() const override;

private:
    void set_point_and_mark(size_t point, std::optional<size_t> mark = {});
    void insert_text(std::string const&, std::optional<size_t> point = {});
    void erase(size_t point, size_t len);
    void move_point(size_t point);
    void update_internals(bool select, size_t line = -1);
    void add_edit_action(EditAction);
    void fill_lines();

    fs::path m_path {};
    bool m_dirty { false };
    FileType m_filetype;
    std::unique_ptr<Mode> m_mode;

    bool m_changed { false };
    Text m_text;

    size_t m_screen_top {0};
    size_t m_screen_left {0};
    size_t m_point {0};
    size_t m_mark {0};
    std::string m_find_term;
    bool m_found { true };
    std::vector<EditAction> m_edits;
    std::optional<size_t> m_undo_pointer {};
    std::chrono::milliseconds m_last_parse_time { 0 };
    static DocumentCommands s_document_commands;

    friend EditAction;
};

}
