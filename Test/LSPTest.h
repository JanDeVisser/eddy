/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <gtest/gtest.h>

#include <LSP/LSP.h>

namespace scratch::test {

using namespace testing;
using namespace scratch::lsp;

class LSPTest : public Test {
protected:
    void SetUp() override {};
};

}
