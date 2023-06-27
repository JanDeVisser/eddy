/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <SDL2_gfxPrimitives.h>

#include <Widget/App.h>
#include <Widget/Widget.h>

namespace eddy {

WindowedWidget::WindowedWidget(SizePolicy policy, size_t size)
    : Widget()
    , m_policy(policy)
    , m_size(size)
{
}

WindowedWidget::WindowedWidget(SizeCalculator calculator)
    : Widget()
    , m_policy(SizePolicy::Calculated)
    , m_size_calculator(std::move(calculator))
{
}

SizePolicy WindowedWidget::policy() const
{
    return m_policy;
}

size_t WindowedWidget::policy_size() const
{
    return m_size;
}

WidgetContainer const* WindowedWidget::parent() const
{
    return m_parent;
}

Position WindowedWidget::position() const
{
    return m_outline.position;
}

Size WindowedWidget::size() const
{
    return m_outline.size;
}

size_t WindowedWidget::top() const
{
    return position().top();
}

size_t WindowedWidget::left() const
{
    return position().left();
}

size_t WindowedWidget::height() const
{
    return size().height();
}

size_t WindowedWidget::width() const
{
    return size().width();
}

bool WindowedWidget::empty() const
{
    return width() == 0 && height() == 0;
}

Box const& WindowedWidget::outline() const
{
    return m_outline;
}

void WindowedWidget::set_renderer(Renderer renderer)
{
    m_renderer = std::move(renderer);
}

void WindowedWidget::set_keyhandler(KeyHandler handler)
{
    m_keyhandler = std::move(handler);
}

void WindowedWidget::set_texthandler(TextHandler handler)
{
    m_texthandler = std::move(handler);
}

void WindowedWidget::set_mousedownhandler(MouseButtonHandler handler)
{
    m_mousedownhandler = std::move(handler);
}

void WindowedWidget::set_mouseclickhandler(MouseButtonHandler handler)
{
    m_mouseclickhandler = std::move(handler);
}

void WindowedWidget::set_mousewheelhandler(MouseWheelHandler handler)
{
    m_mousewheelhandler = std::move(handler);
}

void WindowedWidget::set_mousemotionhandler(MouseMotionHandler handler)
{
    m_mousemotionhandler = std::move(handler);
}

void WindowedWidget::set_size_calculator(SizeCalculator calculator)
{
    m_size_calculator = std::move(calculator);
    m_policy = SizePolicy::Calculated;
}

void WindowedWidget::render()
{
    if (m_renderer != nullptr)
        m_renderer(this);
}

bool WindowedWidget::dispatch(SDL_Keysym sym)
{
    if (m_keyhandler != nullptr)
        return m_keyhandler(this, sym);
    return false;
}

void WindowedWidget::handle_mousedown(SDL_MouseButtonEvent const& event)
{
    if (m_mousedownhandler != nullptr)
        m_mousedownhandler(this, event);
}

void WindowedWidget::handle_click(SDL_MouseButtonEvent const& event)
{
    if (m_mouseclickhandler != nullptr)
        m_mouseclickhandler(this, event);
}

void WindowedWidget::handle_wheel(SDL_MouseWheelEvent const& event)
{
    if (m_mousewheelhandler != nullptr)
        m_mousewheelhandler(this, event);
}

void WindowedWidget::handle_motion(SDL_MouseMotionEvent const& event)
{
    if (m_mousemotionhandler != nullptr)
        m_mousemotionhandler(this, event);
}

void WindowedWidget::handle_text_input()
{
    if (m_texthandler != nullptr)
        m_texthandler(this);
}

void WindowedWidget::resize(Box const& outline)
{
    m_outline = outline;
}

size_t WindowedWidget::calculate_size()
{
    assert(m_policy == SizePolicy::Calculated && m_size_calculator != nullptr);
    return m_size_calculator(this);
}

SDL_Rect WindowedWidget::_render_text(size_t x, size_t y, std::string const& text, SDL_Color const& color, TextAlignment alignment, SDLContext::SDLFontFamily family) const
{
    SDL_Rect ret;
    switch (alignment) {
    case TextAlignment::Left:
        ret = App::instance().context()->render_text(
            left() + x,
            top() + y,
            text, color, family);
        break;
    case TextAlignment::Right:
        ret = App::instance().context()->render_text_right_aligned(left() + x, top() + y,
            text, color, family);
    case TextAlignment::Center:
        ret = App::instance().context()->render_text_centered(left() + width()/2, top() + y,
            text, color, family);
    }
    ret.x -= static_cast<int>(left());
    ret.y -= static_cast<int>(top());
    return ret;
}

void WindowedWidget::_box(SDL_Rect const& rect, SDL_Color color) const
{
    boxColor(
        App::instance().renderer(),
        static_cast<int>(left()) + rect.x,
        static_cast<int>(top()) + rect.y,
        static_cast<int>(left()) + rect.x + rect.w,
        static_cast<int>(top()) + rect.y + rect.h,
        *((uint32_t*)&color));
}

void WindowedWidget::_rectangle(SDL_Rect const& rect, SDL_Color color) const
{
    rectangleColor(
        App::instance().renderer(),
        static_cast<Sint16>(left()) + rect.x,
        static_cast<Sint16>(top()) + rect.y,
        static_cast<Sint16>(left()) + rect.x + rect.w,
        static_cast<Sint16>(top()) + rect.y + rect.h,
        *((uint32_t*)&color));
}

void WindowedWidget::_roundedRectangle(SDL_Rect const& rect, int radius, SDL_Color color) const
{
    roundedRectangleColor(
        App::instance().renderer(),
        static_cast<Sint16>(left()) + rect.x,
        static_cast<Sint16>(top()) + rect.y,
        static_cast<Sint16>(left()) + rect.x + rect.w,
        static_cast<Sint16>(top()) + rect.y + rect.h,
        static_cast<Sint16>(radius),
        *((uint32_t*)&color));
}

}
