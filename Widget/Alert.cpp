/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "SDLContext.h"
#include <Widget/Alert.h>
#include <Widget/App.h>

namespace eddy {

Alert::Alert(std::string text)
    : ModalWidget(App::instance().context()->text_width(text, GraphicsContext::FontFamily::Fixed) * 1.4, App::instance().context()->character_height() * 1.6)
    , m_text(std::move(text))
{
}

void Alert::render()
{
    box(0, 0, 0, 0, Color { 0x2c, 0x2c, 0x2c, 0xff });
    rectangle(2, 2, width() - 4, height() - 4, { 0xff, 0xff, 0xff, 0xff });
    render_fixed_centered(App::instance().context()->character_height() * 0.8, m_text);
}

bool Alert::dispatch(SDL_Keysym sym)
{
    switch (sym.sym) {
    case SDLK_ESCAPE:
    case SDLK_RETURN: {
        this->dismiss();
        return true;
    }
    default:
        return false;
    }
}

}
