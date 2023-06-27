/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <App/Buffer.h>

namespace eddy {

PaletteIndex color_for(TokenCode code)
{
    PaletteIndex color;
    switch (code) {
    case TokenCode::Comment:
        color = PaletteIndex::Comment;
        break;
    case TokenCode::Identifier:
        color = PaletteIndex::Identifier;
        break;
    case TokenCode::DoubleQuotedString:
        color = PaletteIndex::CharLiteral;
        break;
    case TokenCode::SingleQuotedString:
        color = PaletteIndex::String;
        break;
    case TokenCode::Text:
        color = PaletteIndex::Default;
        break;
    default:
        color = PaletteIndex::Punctuation;
        break;
    }
    return color;
}

}
