/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "../LSP/JSON.h"
#include <gtest/gtest.h>

using namespace eddy::lsp;

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
    auto s = value.serialize();
    EXPECT_EQ(s, "{ \"foo\": 42 }");
}

TEST(JSONTest, DecodeObject)
{
    std::string s { "{ \"foo\": 42 }" };
    auto result = JSONValue::deserialize(s);
    EXPECT_FALSE(result.is_error());
    auto value = *result;
    EXPECT_EQ(value.type(), JSONType::Object);
    EXPECT_EQ(value.size(), 1);
    EXPECT_EQ(value["foo"].type(), JSONType::Integer);
    EXPECT_EQ(value["foo"].to_int<int>(), 42);
}

TEST(JSONTest, DecodeIntoVariant)
{
    JSONValue value = JSONValue(42);
    std::variant<float,int,bool> variant;
    auto err_maybe = decode_value(value, variant);
    EXPECT_FALSE(err_maybe.is_error());
    EXPECT_EQ(std::get<int>(variant), 42);
}

TEST(JSONTest, EncodeOptional)
{
    std::optional<int> optional { 42 };
    JSONValue obj = JSONValue::object();
    set(obj, "optional", optional);
    ASSERT_TRUE(obj.has("optional"));
    auto value = *(obj.get("optional"));
    ASSERT_EQ(value.type(), JSONType::Integer);
    EXPECT_EQ(*value.to_int<int>(), 42);
}

TEST(JSONTest, EncodeVariant)
{
    std::variant<int, bool> variant { 42 };
    JSONValue obj = JSONValue::object();
    set(obj, "variant", variant);
    ASSERT_TRUE(obj.has("variant"));
    auto value = *(obj.get("variant"));
    ASSERT_EQ(value.type(), JSONType::Integer);
    EXPECT_EQ(*value.to_int<int>(), 42);
}

TEST(JSONTest, EncodeOptionalVector)
{
    std::optional<std::vector<int>> optional { { 42 } };
    JSONValue obj = JSONValue::object();
    set(obj, "optional", optional);
    ASSERT_TRUE(obj.has("optional"));
    auto value = *(obj.get("optional"));
    ASSERT_EQ(value.type(), JSONType::Array);
    auto elem = *(value.get(0));
    EXPECT_EQ(*elem.to_int<int>(), 42);
}

TEST(JSONTest, EncodeOptionalVariantVectorInt)
{
    std::optional<std::variant<std::vector<int>, int>> optional { std::vector<int> { 42 } };
    JSONValue obj = JSONValue::object();
    set(obj, "optional", optional);
    ASSERT_TRUE(obj.has("optional"));
    auto value = *(obj.get("optional"));
    ASSERT_EQ(value.type(), JSONType::Array);
    auto elem = *(value.get(0));
    EXPECT_EQ(*elem.to_int<int>(), 42);
}
