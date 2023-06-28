/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>

#include <Widget/Geometry.h>

namespace eddy {

class GraphicsContext {
public:
    enum class FontFamily {
        Fixed,
        Proportional,
        Max
    };
    virtual ~GraphicsContext();

    [[nodiscard]] size_t width() const { return m_width; }
    [[nodiscard]] size_t height() const { return m_height; }
    void resize(size_t, size_t);

    [[nodiscard]] virtual size_t character_width() const = 0;
    [[nodiscard]] virtual size_t character_height() const = 0;
    virtual void enlarge_font(FontFamily) = 0;
    virtual void shrink_font(FontFamily) = 0;
    virtual void reset_font(FontFamily) = 0;
    virtual void set_font(std::string const&, FontFamily) = 0;
    virtual void set_font_size(size_t, FontFamily) = 0;

    [[nodiscard]] virtual Box render_text(size_t x, size_t y, std::string const& text, Color const& color, FontFamily) const = 0;
    [[nodiscard]] virtual Box render_text_right_aligned(size_t x, size_t y, std::string const& text, Color const& color, FontFamily) const = 0;
    [[nodiscard]] virtual Box render_text_centered(size_t x, size_t y, std::string const& text, Color const& color, FontFamily) const = 0;
    [[nodiscard]] virtual size_t text_width(std::string const&, FontFamily) const = 0;

    virtual void box(Box const& rect, Color const& color) = 0;
    virtual void roundedBox(Box const& rect, int radius, Color const& color) = 0;
    virtual void rectangle(Box const& rect, Color const& color) = 0;
    virtual void roundedRectangle(Box const& rect, int radius, Color const& color) = 0;

protected:
    GraphicsContext(size_t width, size_t height);

private:
    size_t m_width { 0 };
    size_t m_height { 0 };
};

}
