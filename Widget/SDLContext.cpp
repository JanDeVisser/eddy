/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <sstream>

#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <Widget/SDLContext.h>

using namespace Obelix;

namespace eddy {

SDLContext::SDLInit::SDLInit()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        fatal("Failed to initialize SDL system");
    init = true;
    debug(eddy, "Initialized SDL system");
}

SDLContext::SDLInit::~SDLInit()
{
    debug(eddy, "Terminating SDL system");
    if (init) {
        // primitivePurge();  Probably old. What did this do?
        SDL_Quit();
    }
}

SDLContext::SDLTTF::SDLTTF()
{
    if (TTF_Init() < 0)
        fatal("Failed to initialize SDL TTF system");
    init = true;
    debug(eddy, "Initialized SDL TTF system");
}

SDLContext::SDLTTF::~SDLTTF()
{
    debug(eddy, "Terminating SDL TTF system");
    if (init)
        TTF_Quit();
}

SDLContext::SDLIMG::SDLIMG()
{
    if (IMG_Init(IMG_INIT_PNG) < 0)
        fatal("Failed to initialize SDL IMG system");
    init = true;
    debug(eddy, "Initialized SDL IMG system");
}

SDLContext::SDLIMG::~SDLIMG()
{
    debug(eddy, "Terminating SDL IMG system");
    if (init)
        IMG_Quit();
}

SDLContext::SDLWindow::SDLWindow(size_t width, size_t height)
{
    debug(eddy, "Creating SDL window with size {}x{}", width, height);
    if (window = SDL_CreateWindow(
            "Eddy",
            SDL_WINDOWPOS_CENTERED_DISPLAY(0), SDL_WINDOWPOS_CENTERED_DISPLAY(0),
            static_cast<int>(width),
            static_cast<int>(height),
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        window == nullptr)
        fatal("Could not create SDL window");
    SDL_SetWindowMinimumSize(window, static_cast<int>(width), static_cast<int>(height));
    debug(eddy, "Initialized SDL window");
}

SDLContext::SDLWindow::~SDLWindow()
{
    debug(eddy, "Destroying SDL window");
    if (window)
        SDL_DestroyWindow(window);
}

SDLContext::SDLRenderer::SDLRenderer(SDLWindow const& window)
{
    if (renderer = SDL_GetRenderer(window); renderer == nullptr) {
        if (renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); renderer == nullptr)
            fatal("Could not create SDL renderer");
    }
    debug(eddy, "SDL renderer initialized");
}

SDLContext::SDLRenderer::~SDLRenderer()
{
    debug(eddy, "Destroying SDL renderer");
    if (renderer)
        SDL_DestroyRenderer(renderer);
}

SDLContext::SDLFont::SDLFont(SDLRenderer& renderer, std::string font_name, size_t point_size)
    : renderer(renderer)
    , name(std::move(font_name))
    , initial_size(point_size)
    , size(point_size)
{
    set_font(name);
    debug(eddy, "Opened font '{}' w/ character size {}x{}", name, character_width, character_height);
}

SDLContext::SDLFont::~SDLFont()
{
    if (font)
        TTF_CloseFont(font);
}

void SDLContext::SDLFont::set_size(size_t point_size)
{
    size = point_size;
    if (TTF_SetFontSize(font, static_cast<int>(size)) != 0)
        fatal("Error setting size of font {} to {}: {}", name, size, TTF_GetError());
    if (TTF_SizeUTF8(font, "W", &character_width, &character_height) != 0)
        fatal("Error getting size of text: {}", TTF_GetError());
    if (character_height = TTF_FontHeight(font); character_height < 0)
        fatal("Error getting font height: {}", TTF_GetError());
}

void SDLContext::SDLFont::set_font(std::string const& font_name)
{
    name = font_name;
    if (font = TTF_OpenFont(format("fonts/{}.ttf", name).c_str(), static_cast<int>(size)); font == nullptr)
        fatal("Could not load font '{}': {}", name, TTF_GetError());
    set_size(size);
}

Box SDLContext::SDLFont::render(size_t x, size_t y, std::string const& text, SDL_Color color) const
{
    auto rect = make_SDL_Rect(x, y, 0, 0);
    if (text.empty()) {
        return Box(rect);
    }

    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!surface)
        fatal("Error rendering text: {}", TTF_GetError());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
    return Box(rect);
}

Box SDLContext::SDLFont::render_right_aligned(size_t x, size_t y, std::string const& text, SDL_Color color) const
{
    SDL_Rect rect = make_SDL_Rect(x, y, 0, 0);
    if (text.empty()) {
        return Box(rect);
    }

    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!surface)
        fatal("Error rendering text: {}", TTF_GetError());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    rect.x -= rect.w;
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
    return Box(rect);
}

Box SDLContext::SDLFont::render_centered(size_t x, size_t y, std::string const& text, SDL_Color color) const
{
    SDL_Rect rect = make_SDL_Rect(x, y, 0, 0);
    if (text.empty()) {
        return Box(rect);
    }

    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!surface)
        fatal("Error rendering text: {}", TTF_GetError());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    rect.x -= rect.w / 2;
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
    return Box(rect);
}

size_t SDLContext::SDLFont::text_width(std::string const& text) const
{
    int width, height;
    if (TTF_SizeUTF8(font, text.c_str(), &width, &height) != 0)
        fatal("Error getting text width: {}", TTF_GetError());
    return width;
}

SDLContext::SDLCursor::SDLCursor(SDL_SystemCursor cursor_id)
    : id(cursor_id)
{
    if (cursor = SDL_CreateSystemCursor(id); cursor == nullptr)
        fatal("Could not initialize SDL cursor '{}'", (size_t)id);
    debug(eddy, "Initialized SDL cursor '{}'", (int)id);
}

SDLContext::SDLCursor::~SDLCursor()
{
    debug(eddy, "Destroying SDL cursor '{}'", (int)id);
    if (cursor)
        SDL_FreeCursor(cursor);
}

SDLContext::SDLContext(size_t width, size_t height)
    : GraphicsContext(width, height)
{
    if (!TTF_FontFaceIsFixedWidth(m_fonts[(size_t)FontFamily::Fixed].font))
        fatal("Font '{}' is proportional", m_fonts[(size_t)FontFamily::Fixed].name);
    SDL_ShowCursor(1);
}

size_t SDLContext::character_width() const
{
    return m_fonts[(size_t)FontFamily::Fixed].character_width;
}

size_t SDLContext::character_height() const
{
    return m_fonts[(size_t)FontFamily::Fixed].character_height;
}

void SDLContext::enlarge_font(FontFamily family)
{
    set_font_size(static_cast<size_t>(
                      static_cast<double>(m_fonts[(size_t)family].size) * 1.2), family);
}

void SDLContext::shrink_font(FontFamily family)
{
    set_font_size(static_cast<size_t>(static_cast<double>(m_fonts[(size_t)family].size) / 1.2), family);
}

void SDLContext::reset_font(FontFamily family)
{
    set_font_size(m_fonts[(size_t)family].initial_size, family);
}

void SDLContext::set_font(std::string const& name, FontFamily family)
{
    m_fonts[(size_t)family].set_font(name);
}

void SDLContext::set_font_size(size_t points, FontFamily family)
{
    m_fonts[(size_t)family].set_size(points);
}

Box SDLContext::render_text(size_t x, size_t y, std::string const& text, Color const& color, FontFamily family) const
{
    return m_fonts[(size_t)family].render(x, y, text, SDL_Color(color));
}

Box SDLContext::render_text_right_aligned(size_t x, size_t y, std::string const& text, Color const& color, FontFamily family) const
{
    return m_fonts[(size_t)family].render_right_aligned(x, y, text, SDL_Color(color));
}

Box SDLContext::render_text_centered(size_t x, size_t y, std::string const& text, Color const& color, FontFamily family) const
{
    return m_fonts[(size_t)family].render_centered(x, y, text, SDL_Color(color));
}

size_t SDLContext::text_width(std::string const& text, FontFamily family) const
{
    return m_fonts[(size_t)family].text_width(text);
}

void SDLContext::box(Box const& rect, Color const& color)
{
    boxColor(renderer(), rect.left(), rect.top(), rect.left() + rect.width(), rect.top() + rect.height(), *((uint32_t*)&color));
}

void SDLContext::roundedBox(Box const& rect, int radius, Color const& color)
{
    roundedBoxColor(renderer(), rect.left(), rect.top(), rect.left() + rect.width(), rect.top() + rect.height(), radius, *((uint32_t*)&color));
}

void SDLContext::rectangle(Box const& rect, Color const& color)
{
    rectangleColor(renderer(), rect.left(), rect.top(), rect.left() + rect.width(), rect.top() + rect.height(), *((uint32_t*)&color));
}

void SDLContext::roundedRectangle(Box const& rect, int radius, Color const& color)
{
    roundedRectangleColor(renderer(), rect.left(), rect.top(), rect.left() + rect.width(), rect.top() + rect.height(), radius, *((uint32_t*)&color));
}

}
