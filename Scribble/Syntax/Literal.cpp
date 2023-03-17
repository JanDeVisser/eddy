/*
 * Copyright (c) 2022, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Scribble/Syntax/Literal.h>

namespace Scratch::Scribble {

extern_logging_category(scribble);

// -- Literal ---------------------------------------------------------------

Literal::Literal(Token token)
    : Expression(token.location())
    , m_token(std::move(token))
{
}

Token const& Literal::token() const
{
    return m_token;
}

std::string Literal::attributes() const
{
    return format(R"(value="{}")", token().value());
}

std::string Literal::to_string() const
{
    return std::string(token().value());
}

// -- BooleanLiteral --------------------------------------------------------

BooleanLiteral::BooleanLiteral(Token token)
    : Literal(std::move(token))
{
}

// -- CharLiteral -----------------------------------------------------------

CharLiteral::CharLiteral(Token token, bool quote_closed)
    : QuotedString(std::move(token), quote_closed)
{
}

// -- FloatLiteral ----------------------------------------------------------

FloatLiteral::FloatLiteral(Token token)
    : Literal(std::move(token))
{
}
// -- IntLiteral ------------------------------------------------------------

IntLiteral::IntLiteral(Token token)
    : Literal(std::move(token))
{
}

// -- StringLiteral ---------------------------------------------------------

StringLiteral::StringLiteral(Token token, bool quote_closed)
    : QuotedString(std::move(token), quote_closed)
{
}

std::string StringLiteral::string() const
{
    auto s = token().string_value();
    if (s.starts_with('"') && s.ends_with('"'))
        s = s.substr(1, s.length() - 2);
    return s;
}

}
