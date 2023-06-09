/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <iostream>
#include <gtest/gtest.h>

#include "../Token.h"
#include "../Tokenizer.h"
#include "LexerTest.h"
#include <Core/Format.h>

class NumberTest : public LexerTest {
public:
    template <typename T>
    void check_number(std::string const& in, T const& out, Obelix::TokenCode code)
    {
        tokenize(Obelix::format("Foo = {}", in));
        check_codes(6,
            Obelix::TokenCode::Identifier,
            Obelix::TokenCode::Whitespace,
            Obelix::TokenCode::Equals,
            Obelix::TokenCode::Whitespace,
            code,
            Obelix::TokenCode::EndOfFile);
        Obelix::ErrorOr<T, Obelix::SyntaxError> value_or_error = Obelix::token_value<T>(lexer.tokens()[4]);
        EXPECT_FALSE(value_or_error.is_error());
        EXPECT_EQ(value_or_error.value(), out);
    }

    void initialize() override
    {
        add_scanner<Obelix::NumberScanner>(Obelix::NumberScanner::Config { true, false, true, true, true });
        add_scanner<Obelix::IdentifierScanner>();
        add_scanner<Obelix::WhitespaceScanner>(Obelix::WhitespaceScanner::Config { false, false });
    }

    bool debugOn() override
    {
        return false;
    }
};

TEST_F(NumberTest, number_integer)
{
    check_number<int>("1", 1, Obelix::TokenCode::Integer);
}

TEST_F(NumberTest, longer_number_integer)
{
    check_number<int>("69420", 69420, Obelix::TokenCode::Integer);
}

TEST_F(NumberTest, number_float)
{
    check_number<double>("3.14", 3.14, Obelix::TokenCode::Float);
}

TEST_F(NumberTest, number_hex)
{
    check_number<long>("0xDEADC0DE", 3735929054, Obelix::TokenCode::HexNumber);
}

TEST_F(NumberTest, number_dollar_hex)
{
    check_number<long>("$DEADC0DE", 3735929054, Obelix::TokenCode::HexNumber);
}

TEST_F(NumberTest, double_period)
{
    add_scanner<Obelix::NumberScanner>(Obelix::NumberScanner::Config { true, false, true, true, true });
    add_scanner<Obelix::IdentifierScanner>();
    add_scanner<Obelix::KeywordScanner>(Obelix::TokenCode::Keyword18, "..");
    add_scanner<Obelix::WhitespaceScanner>(Obelix::WhitespaceScanner::Config { false, false });
    tokenize("0..10");

    check_codes(4,
        Obelix::TokenCode::Integer,
        Obelix::TokenCode::Keyword18,
        Obelix::TokenCode::Integer,
        Obelix::TokenCode::EndOfFile);
    auto token0_value_or_error = Obelix::token_value<int>(lexer.tokens()[0]);
    EXPECT_FALSE(token0_value_or_error.is_error());
    EXPECT_EQ(token0_value_or_error.value(), 0);
    auto token2_value_or_error = Obelix::token_value<int>(lexer.tokens()[2]);
    EXPECT_FALSE(token2_value_or_error.is_error());
    EXPECT_EQ(token2_value_or_error.value(), 10);
}
