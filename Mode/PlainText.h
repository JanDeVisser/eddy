/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lexer/BasicParser.h>
#include <Mode/Mode.h>

namespace scratch {

class PlainText : public Mode {
public:
    PlainText(Document&);
};

}
