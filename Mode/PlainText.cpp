/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <lexer/BasicParser.h>
#include <App/Document.h>
#include <Mode/PlainText.h>

namespace scratch {

PlainText::PlainText(Document& doc)
    : Mode(doc)
{
}

}
