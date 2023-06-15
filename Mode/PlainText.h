/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Lexer/BasicParser.h>
#include <Mode/Mode.h>

namespace eddy {

class PlainText : public Mode {
public:
    PlainText(Document&);
};

}
