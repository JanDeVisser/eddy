/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Scribble/Syntax/Syntax.h>
#include <Scribble/Syntax/Expression.h>

namespace scratch::scribble {

ABSTRACT_NODE_CLASS(Literal, Expression)
protected:
    explicit Literal(Token);

public:
    [[nodiscard]] std::string attributes() const override;
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] Token const& token() const;
    [[nodiscard]] bool is_complete() const override { return true; }

private:
    Token m_token;
};

NODE_CLASS(IntLiteral, Literal)
public:
    explicit IntLiteral(Token);
};

class QuotedString : public Literal {
public:
    QuotedString(Token token, bool quote_closed)
        : Literal(std::move(token))
        , m_quote_closed(quote_closed)
    {
    }

    [[nodiscard]] bool quote_closed() const { return m_quote_closed; }
    [[nodiscard]] bool is_complete() const override { return m_quote_closed; }

private:
    bool m_quote_closed { true };
};

NODE_CLASS(CharLiteral, QuotedString)
public:
    explicit CharLiteral(Token, bool = true);
};

NODE_CLASS(FloatLiteral, Literal)
public:
    explicit FloatLiteral(Token);
};

NODE_CLASS(StringLiteral, QuotedString)
public:
    explicit StringLiteral(Token, bool = true);
    [[nodiscard]] std::string string() const;
};

NODE_CLASS(BooleanLiteral, Literal)
public:
    explicit BooleanLiteral(Token);
};

}
