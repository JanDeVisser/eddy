/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lexer/BasicParser.h>

namespace Scratch::Scribble {

using namespace Obelix;

class Scribble : public BasicParser {
public:
    constexpr static TokenCode KeywordBreak = TokenCode::Keyword0;
    constexpr static TokenCode KeywordCase = TokenCode::Keyword1;
    constexpr static TokenCode KeywordCmd = TokenCode::Keyword2;
    constexpr static TokenCode KeywordConst = TokenCode::Keyword3;
    constexpr static TokenCode KeywordContinue = TokenCode::Keyword4;
    constexpr static TokenCode KeywordDecEquals = TokenCode::Keyword5;
    constexpr static TokenCode KeywordDefault = TokenCode::Keyword6;
    constexpr static TokenCode KeywordElif = TokenCode::Keyword7;
    constexpr static TokenCode KeywordElse = TokenCode::Keyword8;
    constexpr static TokenCode KeywordFor = TokenCode::Keyword9;
    constexpr static TokenCode KeywordFunc = TokenCode::Keyword10;
    constexpr static TokenCode KeywordIf = TokenCode::Keyword11;
    constexpr static TokenCode KeywordImport = TokenCode::Keyword12;
    constexpr static TokenCode KeywordIn = TokenCode::Keyword13;
    constexpr static TokenCode KeywordIncEquals = TokenCode::Keyword14;
    constexpr static TokenCode KeywordIntrinsic = TokenCode::Keyword15;
    constexpr static TokenCode KeywordLink = TokenCode::Keyword16;
    constexpr static TokenCode KeywordRange = TokenCode::Keyword17;
    constexpr static TokenCode KeywordReturn = TokenCode::Keyword18;
    constexpr static TokenCode KeywordSwitch = TokenCode::Keyword19;
    constexpr static TokenCode KeywordVar = TokenCode::Keyword20;
    constexpr static TokenCode KeywordWhile = TokenCode::Keyword21;

    constexpr static TokenCode KeywordTrue = TokenCode::Keyword31;
    constexpr static TokenCode KeywordFalse = TokenCode::Keyword32;

    constexpr static TokenCode OutputLine = TokenCode::Keyword33;
    constexpr static TokenCode ExecutionResult = TokenCode::Keyword34;

    constexpr static TokenCode OKPrompt = TokenCode::Keyword35;
    constexpr static TokenCode ErrorPrompt = TokenCode::Keyword36;
    constexpr static TokenCode ContinuationPrompt = TokenCode::Keyword37;

    explicit Scribble(bool = false);

private:
    bool m_ignore_ws { false };
};

} // Scratch::Scribble
