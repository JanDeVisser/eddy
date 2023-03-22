/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <gtest/gtest.h>

#include <App/Console.h>
#include <Scribble/Interp/Interpreter.h>
#include <Scribble/Interp/Function.h>
#include <Scribble/Interp/Value.h>

namespace scratch::test {

using namespace testing;
using namespace Scratch::Interp;

class ScribbleTest : public Test {
protected:
    void SetUp() override {};

    InterpreterContext m_ctx;
};

}
