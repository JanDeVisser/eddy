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

} // scratch::test
