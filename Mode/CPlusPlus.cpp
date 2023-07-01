/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <App/Document.h>
#include <Mode/CPlusPlus.h>

namespace eddy {

CPlusPlusParser::CPlusPlusParser()
    : m_lexer(std::make_unique<BasicParser>())
{
    m_lexer->lexer().add_scanner<Obelix::QStringScanner>("\"'", true);
    m_lexer->lexer().add_scanner<Obelix::IdentifierScanner>();
    m_lexer->lexer().add_scanner<Obelix::NumberScanner>(Obelix::NumberScanner::Config { true, false, true, false, true });
    m_lexer->lexer().add_scanner<Obelix::WhitespaceScanner>(Obelix::WhitespaceScanner::Config { false, false, false });
    m_lexer->lexer().add_scanner<Obelix::CommentScanner>(true,
        Obelix::CommentScanner::CommentMarker { false, false, "/*", "*/" },
        Obelix::CommentScanner::CommentMarker { false, true, "//", "" });
    m_lexer->lexer().add_scanner<Obelix::KeywordScanner>(
        KeywordAuto, "auto",
        KeywordBreak, "break",
        KeywordCase, "case",
        KeywordClass, "class",
        KeywordConst, "const",
        KeywordContinue, "continue",
        KeywordDefault, "default",
        KeywordElse, "else",
        KeywordEnum, "enum",
        KeywordFor, "for",
        KeywordIf, "if",
        KeywordNamespace, "namespace",
        KeywordReturn, "return",
        KeywordStatic, "static",
        KeywordStruct, "struct",
        KeywordSwitch, "switch",
        KeywordUsing, "using",
        KeywordWhile, "while",

        KeywordTrue, "true",
        KeywordFalse, "false",
        KeywordNullptr, "nullptr",

        KeywordDefine, "#define",
        KeywordElif, "#elif",
        KeywordElifdef, "#elifdef",
        KeywordHashElse, "#else",
        KeywordEndif, "#endif",
        KeywordHashIf, "#if",
        KeywordIfdef, "#ifdef",
        KeywordIfndef, "#ifndef",
        KeywordInclude, "#include",
        KeywordPragma, "#pragma");
}

void CPlusPlusParser::assign(std::string_view text)
{
    m_lexer->assign(text);
}

Token const& CPlusPlusParser::lex()
{
    if (!m_pending.empty()) {
        auto const& token = m_pending.front();
        m_pending.pop_front();
        return token;
    }

    while (m_pending.empty()) {
        auto const& token = m_lexer->lex();
        switch (token.code()) {
        case TokenCode::NewLine:
            m_pending.emplace_back(token);
            break;

        case KeywordInclude:
            m_pending.emplace_back(token.location(), TokenDirective, token.value());
            parse_include();
            break;

        case KeywordDefine:
            m_pending.emplace_back(token.location(), TokenDirective, token.value());
            parse_define();
            break;

        case KeywordHashIf:
        case KeywordElif:
        case KeywordPragma:
            m_pending.emplace_back(token.location(), TokenDirective, token.value());
            parse_hashif();
            break;

        case KeywordIfdef:
        case KeywordIfndef:
        case KeywordElifdef:
            m_pending.emplace_back(token.location(), TokenDirective, token.value());
            parse_ifdef();
            break;

        case KeywordEndif:
        case KeywordHashElse:
            m_pending.emplace_back(token.location(), TokenDirective, token.value());
            break;

        case KeywordClass:
        case KeywordStruct:
            m_pending.emplace_back(token.location(), TokenKeyword, token.value());
            if (m_lexer->peek().code() == TokenCode::Identifier) {
                auto const& identifier = m_lexer->lex();
                m_pending.emplace_back(identifier.location(), TokenType, identifier.value());
            }
            break;

        case KeywordAuto:
        case KeywordConst:
        case KeywordIf:
        case KeywordElse:
        case KeywordNamespace:
        case KeywordWhile:
        case KeywordEnum:
        case KeywordFor:
        case KeywordReturn:
        case KeywordSwitch:
        case KeywordCase:
        case KeywordBreak:
        case KeywordContinue:
        case KeywordDefault:
        case KeywordStatic:
        case KeywordUsing:
            m_pending.emplace_back(token.location(), TokenKeyword, token.value());
            break;

        case KeywordNullptr:
        case KeywordTrue:
        case KeywordFalse:
            m_pending.emplace_back(token.location(), TokenConstant, token.value());
            break;

        default:
            m_pending.emplace_back(token);
            break;
        }
    }

    auto const& token = m_pending.front();
    m_pending.pop_front();
    return token;
}

void CPlusPlusParser::parse_include()
{
    Token t = lex_whitespace();
    switch (t.code()) {
    case Obelix::TokenCode::DoubleQuotedString:
        m_lexer->lex();
        m_pending.emplace_back(t.location(), TokenDirectiveParam, t.value());
        break;
    case TokenCode::LessThan: {
        m_lexer->lex();
        auto include = std::string(t.value());
        auto start_loc = t.location();
        Span end_loc;
        do {
            t = m_lexer->lex();
            include += t.value();
            end_loc = t.location();
        } while (t.code() != Obelix::TokenCode::GreaterThan);
        m_pending.emplace_back(start_loc.merge(end_loc), TokenDirectiveParam, include);
        break;
    }
    default:
        break;
    }
}

void CPlusPlusParser::parse_define()
{
    Token t = lex_whitespace();
    if (t.code() != TokenCode::Identifier)
        return;
    t = get_next(TokenMacroName);
    if (t.code() == TokenCode::OpenParen) {
        t = get_next();
        while (true) {
            if (t.code() != TokenCode::Identifier)
                return;
            t = get_next(TokenMacroParam);
            if (t.code() == TokenCode::CloseParen) {
                m_lexer->lex();
                m_pending.emplace_back(t);
                break;
            }
            if (t.code() != TokenCode::Comma)
                return;
            t = get_next();
        }
    }

    auto escape { false };
    std::string def_string;
    lex_whitespace();
    t = m_lexer->peek();
    auto start_loc = t.location();
    auto end_loc = start_loc;
    while (true) {
        switch (t.code()) {
        case TokenCode::Comment:
            m_pending.emplace_back(start_loc.merge(end_loc), TokenMacroExpansion, def_string);
            return;
        case TokenCode::Backslash: {
            m_lexer->lex();
            escape = !escape;
            def_string += t.value();
            break;
        }
        case TokenCode::NewLine:
            m_lexer->lex();
            m_pending.emplace_back(start_loc.merge(end_loc), TokenMacroExpansion, def_string);
            m_pending.emplace_back(t.location(), TokenCode::NewLine, "\n");
            if (!escape)
                return;
            def_string = "";
            escape = false;
            break;
        default:
            escape = false;
            m_lexer->lex();
            def_string += t.value();
            break;
        }
        t = m_lexer->peek();
        end_loc = t.location();
    }
}

void CPlusPlusParser::parse_ifdef()
{
    Token t = lex_whitespace();
    if (t.code() != TokenCode::Identifier)
        return;
    m_lexer->lex();
    m_pending.emplace_back(t.location(), TokenDirectiveParam, t.value());
}

void CPlusPlusParser::parse_hashif()
{
    Token t = lex_whitespace();
    auto escape { false };
    std::string expr;
    t = m_lexer->peek();
    auto start_loc = t.location();
    auto end_loc = t.location();
    while (true) {
        switch (t.code()) {
        case TokenCode::Comment:
            m_pending.emplace_back(start_loc.merge(end_loc), TokenDirectiveParam, expr);
            return;
        case TokenCode::Backslash: {
            m_lexer->lex();
            escape = !escape;
            expr += t.value();
            break;
        }
        case TokenCode::NewLine:
            m_lexer->lex();
            m_pending.emplace_back(start_loc.merge(end_loc), TokenDirectiveParam, expr);
            m_pending.emplace_back(t.location(), TokenCode::NewLine, "\n");
            if (!escape)
                return;
            expr = "";
            escape = false;
            break;
        default:
            escape = false;
            m_lexer->lex();
            expr += t.value();
            break;
        }
        t = m_lexer->peek();
        end_loc = t.location();
    }
}

Token const& CPlusPlusParser::lex_whitespace()
{
    if (m_lexer->peek().code() != TokenCode::Whitespace)
        return m_lexer->peek();
    m_pending.emplace_back(m_lexer->lex());
    return m_pending.back();
}

Token const& CPlusPlusParser::get_next(TokenCode code)
{
    Token t = m_lexer->lex();
    m_pending.emplace_back(t.location(), (code != TokenCode::Unknown) ? code : t.code(), t.value());
    return lex_whitespace();
}

CPlusPlus::CPlusPlus(Document& doc)
    : Mode(doc)
{
    parse = [this](Text& text) {
        CPlusPlusParser parser;
        text.parse(parser, *this);
    };
    color_for = [](TokenCode code) -> PaletteIndex {
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
        case CPlusPlusParser::TokenKeyword:
        case CPlusPlusParser::TokenConstant:
            color = PaletteIndex::Keyword;
            break;
        case CPlusPlusParser::TokenDirective:
            color = PaletteIndex::Preprocessor;
            break;
        default:
            color = plain_color_for(code);
            break;
        }
        return color;
    };
}

}
