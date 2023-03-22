/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lexer/BasicParser.h>

namespace scratch::scribble {

using namespace Obelix;

class Scribble : public BasicParser {
public:
    constexpr static TokenCode KeywordBitwiseAndEquals = TokenCode::Keyword0;
    constexpr static TokenCode KeywordBitwiseOrEquals = TokenCode::Keyword1;
    constexpr static TokenCode KeywordBitwiseXorEquals = TokenCode::Keyword2;
    constexpr static TokenCode KeywordBreak = TokenCode::Keyword3;
    constexpr static TokenCode KeywordCase = TokenCode::Keyword4;
    constexpr static TokenCode KeywordCmd = TokenCode::Keyword5;
    constexpr static TokenCode KeywordConst = TokenCode::Keyword6;
    constexpr static TokenCode KeywordContinue = TokenCode::Keyword7;
    constexpr static TokenCode KeywordDecEquals = TokenCode::Keyword8;
    constexpr static TokenCode KeywordDefault = TokenCode::Keyword9;
    constexpr static TokenCode KeywordDivEquals = TokenCode::Keyword10;
    constexpr static TokenCode KeywordElif = TokenCode::Keyword11;
    constexpr static TokenCode KeywordElse = TokenCode::Keyword12;
    constexpr static TokenCode KeywordFor = TokenCode::Keyword13;
    constexpr static TokenCode KeywordFunc = TokenCode::Keyword14;
    constexpr static TokenCode KeywordIf = TokenCode::Keyword15;
    constexpr static TokenCode KeywordImport = TokenCode::Keyword16;
    constexpr static TokenCode KeywordIn = TokenCode::Keyword17;
    constexpr static TokenCode KeywordIncEquals = TokenCode::Keyword18;
    constexpr static TokenCode KeywordIntrinsic = TokenCode::Keyword19;
    constexpr static TokenCode KeywordLink = TokenCode::Keyword20;
    constexpr static TokenCode KeywordModEquals = TokenCode::Keyword21;
    constexpr static TokenCode KeywordMultEquals = TokenCode::Keyword22;
    constexpr static TokenCode KeywordRange = TokenCode::Keyword23;
    constexpr static TokenCode KeywordReturn = TokenCode::Keyword24;
    constexpr static TokenCode KeywordShlEquals = TokenCode::Keyword25;
    constexpr static TokenCode KeywordShrEquals = TokenCode::Keyword26;
    constexpr static TokenCode KeywordSwitch = TokenCode::Keyword27;
    constexpr static TokenCode KeywordVar = TokenCode::Keyword28;
    constexpr static TokenCode KeywordWhile = TokenCode::Keyword29;

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
