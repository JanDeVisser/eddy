/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Widget/App.h>
#include <Widget/Widget.h>

namespace eddy {

ModalWidget::ModalWidget(int w, int h)
    : m_width(w)
    , m_height(h)
{
}

size_t ModalWidget::width() const
{
    return m_width;
}

size_t ModalWidget::height() const
{
    return m_height;
}

size_t ModalWidget::top() const
{
    return (App::instance().height() - height()) / 2;
}

size_t ModalWidget::left() const
{
    return (App::instance().width() - width()) / 2;
}

void ModalWidget::dismiss()
{
    if (App::instance().modal() == this)
        App::instance().dismiss_modal();
}

}
