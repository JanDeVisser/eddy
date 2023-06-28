/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <cstdlib>

#include <Widget/GraphicsContext.h>

namespace eddy {

GraphicsContext::GraphicsContext(size_t width, size_t height)
    : m_width(width)
    , m_height(height)
{
}

GraphicsContext::~GraphicsContext()
{
}

void GraphicsContext::resize(size_t width, size_t height)
{
    m_width = width;
    m_height = height;
}

}
