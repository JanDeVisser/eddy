/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */
#include <Test/ScribbleTest.h>

namespace scratch::test {

TEST_F(ScribbleTest, Var)
{
    Scratch::ConsoleStatement stmt;
    stmt.compile("var x = \n42");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 42 });
}

TEST_F(ScribbleTest, Assign)
{
    Scratch::ConsoleStatement stmt;
    stmt.compile("var x = 42\nx = 12\nx\n");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 12 });
}

TEST_F(ScribbleTest, VarAdd)
{
    Scratch::ConsoleStatement stmt;
    stmt.compile("var x = \n42  var y = x + 12");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 54 });
}

TEST_F(ScribbleTest, VarMult)
{
    Scratch::ConsoleStatement stmt;
    stmt.compile("var x = \n42  var y = x + 12 var z = y * 2");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 108 });
}

TEST_F(ScribbleTest, FuncDef)
{
    Scratch::ConsoleStatement stmt;
    stmt.compile("func foo(x) { return 2*x }");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Null);
}

TEST_F(ScribbleTest, FuncCall)
{
    Scratch::ConsoleStatement stmt;
    stmt.compile("func foo(x) { return 2*x }   foo(4)");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 8 });
}

TEST_F(ScribbleTest, If)
{
    Scratch::ConsoleStatement stmt;
    stmt.compile("var x = 2 var y = 0 if x > y { y = 3 } else { y = 4 } y");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 3);
}

TEST_F(ScribbleTest, While)
{
    Scratch::ConsoleStatement stmt;
    stmt.compile("var x = 2 var y = 0 while y < 10 { x = x + y y = y + 1 } x");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 47);
}

} // scratch::test
