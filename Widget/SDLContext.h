/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <array>
#include <map>
#include <memory>

#include <SDL.h>
#include <SDL_ttf.h>

#include <Core/Logging.h>

#include <Widget/GraphicsContext.h>

using namespace Obelix;

namespace eddy {

extern_logging_category(eddy);

class SDLContext : public GraphicsContext {
public:
    SDLContext(size_t width, size_t height);
    ~SDLContext() = default;

    SDL_Window* window() { return m_window; }
    SDL_Renderer* renderer() { return m_renderer; }
    SDL_Cursor* arrow() { return m_arrow; }
    SDL_Cursor* input() { return m_arrow; }

    [[nodiscard]] size_t character_width() const override;
    [[nodiscard]] size_t character_height() const override;
    void enlarge_font(FontFamily) override;
    void shrink_font(FontFamily) override;
    void reset_font(FontFamily) override;
    void set_font(std::string const&, FontFamily) override;
    void set_font_size(size_t, FontFamily) override;

    Box render_text(size_t x, size_t y, std::string const& text, Color const& color, FontFamily) const override;
    Box render_text_right_aligned(size_t x, size_t y, std::string const& text, Color const& color, FontFamily) const override;
    Box render_text_centered(size_t x, size_t y, std::string const& text, Color const& color, FontFamily) const override;
    size_t text_width(std::string const&, FontFamily) const override;

    void box(Box const& rect, Color const& color) override;
    void roundedBox(Box const& rect, int radius, Color const& color) override;
    void rectangle(Box const& rect, Color const& color) override;
    void roundedRectangle(Box const& rect, int radius, Color const& color) override;
private:
    struct SDLInit {
        SDLInit();
        ~SDLInit();
        bool init { false };
    };

    struct SDLTTF {
        SDLTTF();
        ~SDLTTF();
        bool init { false };
    };

    struct SDLIMG {
        SDLIMG();
        ~SDLIMG();
        bool init { false };
    };

    struct SDLWindow {
        SDLWindow(size_t width, size_t height);
        ~SDLWindow();
        operator SDL_Window*() const { return window; }

        SDL_Window* window { nullptr };
    };

    struct SDLRenderer {
        explicit SDLRenderer(SDLWindow const& window);
        ~SDLRenderer();
        operator SDL_Renderer*() const { return renderer; }

        SDL_Renderer* renderer;
    };

    struct SDLFont {
        SDLFont(SDLRenderer&, std::string font_name, size_t point_size);
        ~SDLFont();

        void set_size(size_t);
        void set_font(std::string const&);
        [[nodiscard]] std::string to_string() const { return name; }
        explicit operator TTF_Font*() const { return font; }
        [[nodiscard]] Box render(size_t, size_t, std::string const& text, SDL_Color color) const;
        [[nodiscard]] Box render_right_aligned(size_t, size_t, std::string const& text, SDL_Color color) const;
        [[nodiscard]] Box render_centered(size_t, size_t, std::string const& text, SDL_Color color) const;
        [[nodiscard]] size_t text_width(std::string const&) const;

        SDLRenderer& renderer;
        TTF_Font *font;
        std::string name;
        size_t initial_size;
        size_t size;
        int character_width;
        int character_height;
    };

    struct SDLCursor {
        SDLCursor(SDL_SystemCursor);
        ~SDLCursor();
        operator SDL_Cursor*() const { return cursor; }

        SDL_SystemCursor id;
        SDL_Cursor* cursor;
    };

    SDLInit m_sdl {};
    SDLTTF m_ttf {};
    SDLWindow m_window { width(), height() };
    SDLRenderer m_renderer { m_window };
    SDLIMG m_img {};
    std::array<SDLFont, (size_t)FontFamily::Max> m_fonts {
        SDLFont { m_renderer, "JetBrainsMono", 18 },
        SDLFont { m_renderer, "Swansea-q3pd", 15 }
    };
    SDLCursor m_arrow { SDL_SYSTEM_CURSOR_ARROW };
    SDLCursor m_input { SDL_SYSTEM_CURSOR_IBEAM };
};

}
