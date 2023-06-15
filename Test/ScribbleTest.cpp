/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Test/ScribbleTest.h>

namespace eddy::test {

TEST_F(ScribbleTest, Var)
{
    Eddy::ConsoleStatement stmt;
    stmt.compile("var x = \n42");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 42 });
}

TEST_F(ScribbleTest, Assign)
{
    Eddy::ConsoleStatement stmt;
    stmt.compile("var x = 42\nx = 12\nx\n");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 12 });
}

TEST_F(ScribbleTest, VarAdd)
{
    Eddy::ConsoleStatement stmt;
    stmt.compile("var x = \n42  var y = x + 12");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 54 });
}

TEST_F(ScribbleTest, VarMult)
{
    Eddy::ConsoleStatement stmt;
    stmt.compile("var x = \n42  var y = x + 12 var z = y * 2");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 108 });
}

TEST_F(ScribbleTest, FuncDef)
{
    Eddy::ConsoleStatement stmt;
    stmt.compile("func foo(x) { return 2*x }");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Null);
}

TEST_F(ScribbleTest, FuncCall)
{
    Eddy::ConsoleStatement stmt;
    stmt.compile("func foo(x) { return 2*x }   foo(4)");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 8 });
    stmt.compile("func test-me(x, y) { return x + y }  test-me(3, 5)");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result, Value { 8 });
}

TEST_F(ScribbleTest, If)
{
    Eddy::ConsoleStatement stmt;
    stmt.compile("var x = 2 var y = 0 if x > y { y = 3 } else { y = 4 } y");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 3);
}

TEST_F(ScribbleTest, While)
{
    Eddy::ConsoleStatement stmt;
    stmt.compile("var x = 2 var y = 0 while y < 10 { x = x + y y = y + 1 } x");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 47);
}

TEST_F(ScribbleTest, For)
{
    Eddy::ConsoleStatement stmt;
    stmt.compile("var x = 2 for y in 0..10 { x = x + y } x");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 47);
}

TEST_F(ScribbleTest, Precedence)
{
    Eddy::ConsoleStatement stmt;
    stmt.compile("5*4+2");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 22);

    stmt.compile("5+4*2");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 13);

    stmt.compile("(5+4)*2");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 18);

    stmt.compile("5*(4+2)");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 30);

    stmt.compile("(5*4)+2");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 22);

    stmt.compile("5*4+2*6");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 32);

    stmt.compile("5*(4+2)*6");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 180);
}

TEST_F(ScribbleTest, BuiltInNoArgs)
{
    auto err = register_builtin(m_ctx, "builtin_function",
            [](Eddy::interp::Values const&, InterpreterContext&) {
                return Value { 69 };
            }
        );
    EXPECT_FALSE(err.is_error());
    Eddy::ConsoleStatement stmt;
    stmt.compile("builtin_function()");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 69);
}

TEST_F(ScribbleTest, BuiltInWithArgs)
{
    auto err = register_builtin(m_ctx, "builtin_function",
            [](Eddy::interp::Values const& values, InterpreterContext&) {
                return Value { *(values[0].to_int<int>()) + *(values[1].to_int<int>()) };
            }
        );
    EXPECT_FALSE(err.is_error());
    Eddy::ConsoleStatement stmt;
    stmt.compile("builtin_function(12, 37)");
    EXPECT_NE(stmt.node, nullptr);
    stmt.execute(m_ctx);
    EXPECT_EQ(stmt.result.type(), ValueType::Integer);
    EXPECT_EQ(stmt.result.to_int<int>(), 49);
}

} // Eddy::test
