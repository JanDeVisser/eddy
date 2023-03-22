/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Scribble/Scribble.h>

namespace scratch::scribble {

Scribble::Scribble(bool ignore_ws)
    : BasicParser()
    , m_ignore_ws(ignore_ws)
{
    lexer().add_scanner<Obelix::QStringScanner>("\"'", true);
    IdentifierScanner::Config ident_config;
    ident_config.filter = "X_-";
    lexer().add_scanner<Obelix::IdentifierScanner>(ident_config);
    lexer().add_scanner<Obelix::NumberScanner>(Obelix::NumberScanner::Config { true, false, true, false, true });
    lexer().add_scanner<Obelix::WhitespaceScanner>(Obelix::WhitespaceScanner::Config { m_ignore_ws, m_ignore_ws, m_ignore_ws });
    lexer().add_scanner<Obelix::CommentScanner>(true,
        Obelix::CommentScanner::CommentMarker { false, false, "/*", "*/" },
        Obelix::CommentScanner::CommentMarker { false, true, "//", "" });
    lexer().add_scanner<Obelix::KeywordScanner>(
        KeywordBitwiseAndEquals, "&=",
        KeywordBitwiseOrEquals, "|=",
        KeywordBitwiseXorEquals, "^=",
        KeywordBreak, "break",
        KeywordCase, "case",
        KeywordCmd, "cmd",
        KeywordConst, "const",
        KeywordContinue, "continue",
        KeywordDecEquals, "-=",
        KeywordDefault, "default",
        KeywordDivEquals, "/=",
        KeywordElif, "elif",
        KeywordElse, "else",
        KeywordFor, "for",
        KeywordFunc, "func",
        KeywordIf, "if",
        KeywordImport, "import",
        KeywordIn, "in",
        KeywordIncEquals, "+=",
        KeywordIntrinsic, "intrinsic",
        KeywordLink, "->",
        KeywordModEquals, "%=",
        KeywordMultEquals, "*=",
        KeywordRange, "..",
        KeywordReturn, "return",
        KeywordShlEquals, "<<=",
        KeywordShrEquals, ">>=",
        KeywordSwitch, "switch",
        KeywordVar, "var",
        KeywordWhile, "while",

        KeywordTrue, "true",
        KeywordFalse, "false");
}

} // Scratch::Scribble
