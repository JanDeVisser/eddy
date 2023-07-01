/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Core/FileBuffer.h>
#include <Mode/Mode.h>
#include <Lexer/BasicParser.h>

namespace eddy {


PaletteIndex plain_color_for(TokenCode code)
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

Mode::Mode(Document& doc)
    : m_doc(doc)
{
    open_file = [](fs::path const& path) -> ErrorOr<std::string, SystemError> {
        auto buffer = TRY(FileBuffer::from_file(path));
        return buffer->buffer();
    };
    parse = [this](Text& text) -> void {
        PlainTextParser parser;
        text.parse(parser, *this);
    };
    color_for = [](TokenCode code) -> PaletteIndex {
        return plain_color_for(code);
    };
}

[[nodiscard]] Document const& Mode::document() const
{
    return m_doc;
}

[[nodiscard]] Document& Mode::document()
{
    return m_doc;
}


}
