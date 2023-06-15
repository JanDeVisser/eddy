/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <gtest/gtest.h>

#include <LSP/LSP.h>

namespace eddy::test {

using namespace testing;
using namespace eddy::lsp;

class LSPTest : public Test {
protected:
    void SetUp() override {};
};

}
