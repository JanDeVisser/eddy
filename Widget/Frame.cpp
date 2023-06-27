/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Widget/Widget.h>

namespace eddy {

Frame::Frame(FrameStyle frame_style, size_t margin, WindowedWidget* contents, SizePolicy policy, size_t size)
    : WindowedWidget(policy, size)
    , m_frame_style(frame_style)
    , m_margin(margin)
    , m_contents(contents)
{
    m_margin = clamp(m_margin, 3ul, 255ul);
}

void Frame::render()
{
    auto half_margin = m_clamped_margin / 2;
    switch (m_frame_style) {
    case FrameStyle::Rectangle:
        rectangle(half_margin, half_margin,
            width() - m_clamped_margin, height() - m_clamped_margin, { 0xff, 0xff, 0xff, 0xff });
        break;
    case FrameStyle::Rounded:
        roundedRectangle(
            half_margin, half_margin, width() - m_clamped_margin, height() - m_clamped_margin,
            half_margin,
            { 0xff, 0xff, 0xff, 0xff }
        );
        break;
    default:
        break;
    }
    m_contents->render();
}

bool Frame::dispatch(SDL_Keysym sym)
{
    return m_contents->dispatch(sym);
}

void Frame::resize(Box const& outline)
{
    WindowedWidget::resize(outline);
    m_clamped_margin = clamp(m_margin, 3, std::min(outline.width(), outline.height())/2);
    m_contents->resize( {
        outline.left() + m_clamped_margin, outline.top() + m_clamped_margin,
        outline.width() - 2 * m_clamped_margin, outline.height() - 2 * m_clamped_margin
    } );
}

[[nodiscard]] WindowedWidget* Frame::contents()
{
    return m_contents.get();
}

[[nodiscard]] size_t Frame::margin() const
{
    return m_margin;
}

[[nodiscard]] size_t Frame::clamped_margin() const
{
    return m_clamped_margin;
}

[[nodiscard]] FrameStyle Frame::frame_style() const
{
    return m_frame_style;
}

}
