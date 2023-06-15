/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <App/EditorState.h>
#include <Parser/EddyParser.h>
#include <Lexer/Token.h>

namespace eddy::parser {

class PlainTextParser : public BasicEddyParser {
public:
    PlainTextParser();
    Token const& next_token() override;
    DisplayToken colorize(TokenCode, std::string_view const&) override;

private:
    std::string m_current_line;
};

}
