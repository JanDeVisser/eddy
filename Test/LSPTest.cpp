/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <iostream>

#include <Test/LSPTest.h>
#include <LSP/Message.h>

namespace scratch::test {

using namespace scratch::lsp;

TEST_F(LSPTest, GetTheLSP)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto std_err = lsp.process().standard_error();
    for (auto const& line : std_err) {
        std::cout << line << "\n";
    }
    auto err = lsp.shutdown();
    EXPECT_FALSE(lsp.running());
}

TEST_F(LSPTest, SendExitNotification)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto err = send_notification(lsp, std::string("exit"));
    EXPECT_FALSE(err.is_error());
}

TEST_F(LSPTest, SendShutdownRequest)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto err = send_request<std::string, Void>(lsp, std::string("shutdown"));
    EXPECT_FALSE(err.is_error());
}

} // scratch::test
