/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "../LSP/JSON.h"
#include <gtest/gtest.h>

using namespace Obelix;

TEST(JSONTest, CreateNull)
{
    JSONValue value;
    EXPECT_TRUE(value.is_null());
}

TEST(JSONTest, CreateString)
{
    JSONValue value("hello");
    EXPECT_TRUE(value.is_string());
    EXPECT_EQ(value.to_string(), "hello");
}

TEST(JSONTest, CreateInteger)
{
    JSONValue value(42);
    EXPECT_TRUE(value.is_integer());
    EXPECT_EQ(*value.to_int<int>(), 42);
}

TEST(JSONTest, CreateDouble)
{
    JSONValue value(3.14);
    EXPECT_TRUE(value.is_double());
    EXPECT_DOUBLE_EQ(*value.to_float<double>(), 3.14);
}

TEST(JSONTest, CreateArray)
{
    JSONValue value = JSONValue::array();
    EXPECT_TRUE(value.is_array());
    value.append(JSONValue(42));
    auto arr = *value.to_array();
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0].type(), JSONType::Integer);
    EXPECT_EQ(arr[0].to_int<int>(), 42);
}

TEST(JSONTest, CreateObject)
{
    JSONValue value = JSONValue::object();
    EXPECT_TRUE(value.is_object());
    value.set("foo", JSONValue(42));
    EXPECT_EQ(value.size(), 1);
    EXPECT_EQ(value["foo"].type(), JSONType::Integer);
    EXPECT_EQ(value["foo"].to_int<int>(), 42);
}

TEST(JSONTest, EncodeObject)
{
    JSONValue value = JSONValue::object();
    value.set("foo", JSONValue(42));
    auto s = value.encode();
    EXPECT_EQ(s, "{ \"foo\": 42 }");
}

TEST(JSONTest, DecodeObject)
{
    std::string s { "{ \"foo\": 42 }" };
    auto result = JSONValue::decode(s);
    EXPECT_FALSE(result.is_error());
    auto value = *result;
    EXPECT_EQ(value.type(), JSONType::Object);
    EXPECT_EQ(value.size(), 1);
    EXPECT_EQ(value["foo"].type(), JSONType::Integer);
    EXPECT_EQ(value["foo"].to_int<int>(), 42);
}
