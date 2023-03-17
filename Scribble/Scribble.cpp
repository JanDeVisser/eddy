/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Scribble/Scribble.h>
#include <Scribble/Syntax/Statement.h>

namespace Scratch::Scribble {

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
        KeywordBreak, "break",
        KeywordCase, "case",
        KeywordCmd, "cmd",
        KeywordConst, "const",
        KeywordContinue, "continue",
        KeywordDecEquals, "-=",
        KeywordDefault, "default",
        KeywordElse, "else",
        KeywordElif, "elif",
        KeywordFor, "for",
        KeywordFunc, "func",
        KeywordIf, "if",
        KeywordImport, "import",
        KeywordIn, "in",
        KeywordIncEquals, "+=",
        KeywordIntrinsic, "intrinsic",
        KeywordLink, "->",
        KeywordRange, "..",
        KeywordReturn, "return",
        KeywordSwitch, "switch",
        KeywordVar, "var",
        KeywordWhile, "while",

        KeywordTrue, "true",
        KeywordFalse, "false");
}

} // Scratch::Scribble
