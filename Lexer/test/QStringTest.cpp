/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "../Lexer.h"
#include "../Tokenizer.h"
#include "LexerTest.h"
#include <gtest/gtest.h>

using namespace Obelix;

class QStringTest : public LexerTest {
public:
    void check_qstring(std::string const& in, std::string const& out, bool verbatim = false)
    {
        add_scanner<Obelix::QStringScanner>("\"'`", verbatim);
        add_scanner<Obelix::IdentifierScanner>();
        add_scanner<Obelix::WhitespaceScanner>(Obelix::WhitespaceScanner::Config { false, false });
        tokenize("Hello " + in);
        check_codes(4,
            Obelix::TokenCode::Identifier,
            Obelix::TokenCode::Whitespace,
            Obelix::TokenCode::SingleQuotedString,
            Obelix::TokenCode::EndOfFile);
        EXPECT_EQ(lexer.tokens()[2].value(), out);
    }

    void check_qstring_error(std::string const& in)
    {
        add_scanner<Obelix::QStringScanner>();
        add_scanner<Obelix::IdentifierScanner>();
        add_scanner<Obelix::WhitespaceScanner>(Obelix::WhitespaceScanner::Config { false, false });
        tokenize("Hello " + in);
        check_codes(4,
            Obelix::TokenCode::Identifier,
            Obelix::TokenCode::Whitespace,
            Obelix::TokenCode::Error,
            Obelix::TokenCode::EndOfFile);
    }

    void initialize() override
    {
    }

    bool debugOn() override
    {
        return false;
    }
};

TEST(BasicQStringTest, SingleQuotedString)
{
    Lexer lexer {};
    lexer.add_scanner<QStringScanner>();
    lexer.add_scanner<IdentifierScanner>();
    lexer.add_scanner<Obelix::WhitespaceScanner>(Obelix::WhitespaceScanner::Config { false, false });
    auto tokens = lexer.tokenize(R"('X')");
    EXPECT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0].code(), TokenCode::SingleQuotedString);
    EXPECT_EQ(tokens[0].string_value(), "X");
}

TEST_F(QStringTest, qstring)
{
    add_scanner<Obelix::QStringScanner>();
    add_scanner<Obelix::IdentifierScanner>();
    add_scanner<Obelix::WhitespaceScanner>(Obelix::WhitespaceScanner::Config { false, false });
    tokenize(R"(Hello 'single quotes' `backticks` "double quotes" World)");
    check_codes(10,
        Obelix::TokenCode::Identifier,
        Obelix::TokenCode::Whitespace,
        Obelix::TokenCode::SingleQuotedString,
        Obelix::TokenCode::Whitespace,
        Obelix::TokenCode::BackQuotedString,
        Obelix::TokenCode::Whitespace,
        Obelix::TokenCode::DoubleQuotedString,
        Obelix::TokenCode::Whitespace,
        Obelix::TokenCode::Identifier,
        Obelix::TokenCode::EndOfFile);

    EXPECT_EQ(count_tokens_with_code(Obelix::TokenCode::Identifier), 2);
    EXPECT_EQ(count_tokens_with_code(Obelix::TokenCode::SingleQuotedString), 1);
    EXPECT_EQ(count_tokens_with_code(Obelix::TokenCode::DoubleQuotedString), 1);
    EXPECT_EQ(count_tokens_with_code(Obelix::TokenCode::BackQuotedString), 1);
    EXPECT_EQ(lexer.tokens()[2].value(), "single quotes");
    EXPECT_EQ(lexer.tokens()[4].value(), "backticks");
    EXPECT_EQ(lexer.tokens()[6].value(), "double quotes");
}

TEST_F(QStringTest, qstring_unclosed_string)
{
    check_qstring_error("'no close quote");
}

TEST_F(QStringTest, qstring_escape_backslash)
{
    check_qstring("'escaped backslash \\\\'", "escaped backslash \\");
}

TEST_F(QStringTest, qstring_escape_quote)
{
    check_qstring("'escaped quote\\''", "escaped quote'");
}

TEST_F(QStringTest, qstring_escape_newline)
{
    check_qstring("'escaped\\nnewline'", "escaped\nnewline");
}

TEST_F(QStringTest, qstring_escape_plain_char)
{
    check_qstring("'escaped \\$ dollarsign'", "escaped $ dollarsign");
}

TEST_F(QStringTest, qstring_escape_as_last_char)
{
    check_qstring_error("'escape \\");
}

TEST_F(QStringTest, qstring_verbatim)
{
    add_scanner<Obelix::QStringScanner>("\"'`", true);
    add_scanner<Obelix::IdentifierScanner>();
    add_scanner<Obelix::WhitespaceScanner>(Obelix::WhitespaceScanner::Config { false, false });
    tokenize(R"(Hello 'single quotes' `backticks` "double quotes" World)");
    check_codes(10,
        Obelix::TokenCode::Identifier,
        Obelix::TokenCode::Whitespace,
        Obelix::TokenCode::SingleQuotedString,
        Obelix::TokenCode::Whitespace,
        Obelix::TokenCode::BackQuotedString,
        Obelix::TokenCode::Whitespace,
        Obelix::TokenCode::DoubleQuotedString,
        Obelix::TokenCode::Whitespace,
        Obelix::TokenCode::Identifier,
        Obelix::TokenCode::EndOfFile);

    EXPECT_EQ(count_tokens_with_code(Obelix::TokenCode::Identifier), 2);
    EXPECT_EQ(count_tokens_with_code(Obelix::TokenCode::SingleQuotedString), 1);
    EXPECT_EQ(count_tokens_with_code(Obelix::TokenCode::DoubleQuotedString), 1);
    EXPECT_EQ(count_tokens_with_code(Obelix::TokenCode::BackQuotedString), 1);
    EXPECT_EQ(lexer.tokens()[2].value(), "'single quotes'");
    EXPECT_EQ(lexer.tokens()[4].value(), "`backticks`");
    EXPECT_EQ(lexer.tokens()[6].value(), R"("double quotes")");
}

TEST_F(QStringTest, qstring_escape_newline_verbatim)
{
    check_qstring(R"('escaped\nnewline')", R"('escaped\nnewline')", true);
}
