/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Lexer/BasicParser.h>
#include <Mode/Mode.h>
#include <Parser/CPlusPlus.h>

namespace eddy {

class CPlusPlusParser {
public:
    constexpr static TokenCode KeywordAuto = TokenCode::Keyword0;
    constexpr static TokenCode KeywordBreak = TokenCode::Keyword1;
    constexpr static TokenCode KeywordCase = TokenCode::Keyword2;
    constexpr static TokenCode KeywordClass = TokenCode::Keyword3;
    constexpr static TokenCode KeywordConst = TokenCode::Keyword4;
    constexpr static TokenCode KeywordContinue = TokenCode::Keyword5;
    constexpr static TokenCode KeywordDefault = TokenCode::Keyword6;
    constexpr static TokenCode KeywordElse = TokenCode::Keyword7;
    constexpr static TokenCode KeywordEnum = TokenCode::Keyword8;
    constexpr static TokenCode KeywordFalse = TokenCode::Keyword9;
    constexpr static TokenCode KeywordFor = TokenCode::Keyword10;
    constexpr static TokenCode KeywordIf = TokenCode::Keyword11;
    constexpr static TokenCode KeywordNamespace = TokenCode::Keyword12;
    constexpr static TokenCode KeywordNullptr = TokenCode::Keyword13;
    constexpr static TokenCode KeywordReturn = TokenCode::Keyword14;
    constexpr static TokenCode KeywordStatic = TokenCode::Keyword15;
    constexpr static TokenCode KeywordStruct = TokenCode::Keyword16;
    constexpr static TokenCode KeywordSwitch = TokenCode::Keyword17;
    constexpr static TokenCode KeywordTrue = TokenCode::Keyword18;
    constexpr static TokenCode KeywordUsing = TokenCode::Keyword19;
    constexpr static TokenCode KeywordWhile = TokenCode::Keyword20;

    constexpr static TokenCode KeywordInclude = TokenCode::Keyword21;
    constexpr static TokenCode KeywordDefine = TokenCode::Keyword22;
    constexpr static TokenCode KeywordIfdef = TokenCode::Keyword23;
    constexpr static TokenCode KeywordIfndef = TokenCode::Keyword24;
    constexpr static TokenCode KeywordEndif = TokenCode::Keyword25;
    constexpr static TokenCode KeywordElif = TokenCode::Keyword26;
    constexpr static TokenCode KeywordElifdef = TokenCode::Keyword27;
    constexpr static TokenCode KeywordPragma = TokenCode::Keyword28;
    constexpr static TokenCode KeywordHashIf = TokenCode::Keyword29;
    constexpr static TokenCode KeywordHashElse = TokenCode::Keyword30;

    constexpr static TokenCode TokenKeyword = TokenCode::Keyword81;
    constexpr static TokenCode TokenMacroName = TokenCode::Keyword82;
    constexpr static TokenCode TokenMacroParam = TokenCode::Keyword83;
    constexpr static TokenCode TokenMacroExpansion = TokenCode::Keyword84;
    constexpr static TokenCode TokenDirective = TokenCode::Keyword85;
    constexpr static TokenCode TokenDirectiveParam = TokenCode::Keyword86;
    constexpr static TokenCode TokenType = TokenCode::Keyword87;
    constexpr static TokenCode TokenOperator = TokenCode::Keyword88;
    constexpr static TokenCode TokenConstant = TokenCode::Keyword89;

    CPlusPlusParser();
    void assign(std::string_view text);
    Token const& lex();

private:
    void parse_include();
    void parse_define();
    void parse_hashif();
    void parse_ifdef();
    Token const& lex_whitespace();
    Token const& get_next(TokenCode = TokenCode::Unknown);

    std::deque<Token> m_pending;
    std::unique_ptr<BasicParser> m_lexer;
};

class CPlusPlus : public Mode {
public:
    explicit CPlusPlus(Document&);
};

}
