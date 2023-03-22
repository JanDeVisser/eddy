/*
 * Copyright (c) 2022, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <deque>
#include <filesystem>
#include <sstream>
#include <string>

#include <SDL.h>

#include <core/Logging.h>

#include <App/Palette.h>
#include <Widget/Command.h>
#include <Widget/Geometry.h>
#include <Widget/Key.h>
#include <Widget/Text.h>
#include <Widget/Widget.h>

#ifndef WIDGET_BORDER_X
#define WIDGET_BORDER_X 8
#endif

#ifndef WIDGET_BORDER_Y
#define WIDGET_BORDER_Y 20
#endif

#ifndef SCROLL_BAR_SIZE
#define SCROLL_BAR_SIZE 8
#endif

#ifndef SCRATCH_EPSILON
#define SCRATCH_EPSILON 0.0001f
#endif /* SCRATCH_EPSILON */

#ifndef SCRATCH_UTF8_CHAR_FACTOR
#define SCRATCH_UTF8_CHAR_FACTOR 2
#endif /* SCRATCH_UTF8_CHAR_FACTOR */

#ifndef SCRATCH_MERGE_UNDO_REDO
#define SCRATCH_MERGE_UNDO_REDO 1
#endif /* SCRATCH_MERGE_UNDO_REDO */

#ifndef SCRATCH_CASE_FUNC
#define SCRATCH_CASE_FUNC ::tolower
#endif /* SCRATCH_CASE_FUNC */

#ifndef countof
#define countof(A) (sizeof(A) / sizeof(*(A)))
#endif /* countof */

namespace scratch {

extern_logging_category(widget);

using Key=int;
using Keycode=int32_t;
using InputBuffer = std::basic_string<CodePoint, std::char_traits<CodePoint>, std::allocator<CodePoint>>;

static_assert(sizeof(Keycode) == sizeof(SDL_Keycode), "Wrong type size.");

class SDLContext;

class App : public Layout {
public:
    App(std::string, SDLContext*);
    static App& instance();

    ~App() override = default;
    void quit() { m_quit = true; }

    [[nodiscard]] bool is_running() const { return !m_quit; }
    [[nodiscard]] SDLContext* context() { return m_context.get(); }
    [[nodiscard]] SDLContext const* context() const { return m_context.get(); }
    SDL_Renderer* renderer();
    void enlarge_font();
    void shrink_font();
    void reset_font();
    void set_font(std::string const&);

    SDLKey last_key() const { return m_last_key; }
    Position mouse_position() const { return m_mouse; }

    int width() const override;
    int height() const override;
    intptr_t active() const;
    void active(intptr_t);

    void event_loop();
    virtual void pre_render() { };
    void render() override;
    virtual void post_render() { };
    virtual void on_command(ScheduledCommand const&) { };
    bool dispatch(SDL_Keysym) override;
    void resize(Box const&) override;
    std::string input_buffer();
    void schedule(ScheduledCommand cmd);
    [[nodiscard]] int fps() const;

    void add_modal(Widget*);
    Widget* modal();
    void dismiss_modal();

    [[nodiscard]] Widget* focus();
    void focus(Widget*);

private:
    static App* s_app;

    std::string m_name;
    bool m_quit { false };
    int m_width { 0 };
    int m_height { 0 };
    intptr_t m_active { 0 };

    InputBuffer m_input_characters;

    Vec2 m_widgetPos;
    Vec2 m_widgetSize;

    Vec2 m_contentSize;

    unsigned m_frameCount = 0;

    Widget* m_focus { nullptr };
    std::vector<std::unique_ptr<Widget>> m_modals;
    std::unique_ptr<SDLContext> m_context;
    std::deque<ScheduledCommand> m_pending_commands;
    SDLKey m_last_key { SDLK_UNKNOWN, KMOD_NONE };
    Position m_mouse { 0, 0 };
    std::chrono::duration<double> m_last_render_time { 0.0 };
};

}
