/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <iostream>

#include <Test/LSPTest.h>
#include <LSP/LSPMessages.h>

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

TEST_F(LSPTest, SendInitializeRequest)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto err = send_request<Initialize>(lsp, InitializeParams {});
    EXPECT_FALSE(err.is_error());
    auto& response = err.value();
    EXPECT_FALSE(response.is_error());
}

TEST_F(LSPTest, SendExitNotification)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto init_err = send_request<Initialize>(lsp, InitializeParams {});
    EXPECT_FALSE(init_err.is_error());
    auto err = send_notification<Exit>(lsp);
    EXPECT_FALSE(err.is_error());
}

TEST_F(LSPTest, SendShutdownRequest)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto init_err = send_request<Initialize>(lsp, InitializeParams {});
    EXPECT_FALSE(init_err.is_error());
    auto err = send_request<Shutdown>(lsp);
    EXPECT_FALSE(err.is_error());
}

} // scratch::test
