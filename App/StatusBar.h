/*
 * Copyright (c) 2022, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Widget/App.h>

namespace scratch {

class StatusBar : public Layout {
public:
    explicit StatusBar();
    Frame* add_applet(int, Renderer);
};

}
