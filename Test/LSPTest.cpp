/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <iostream>

#include <Core/FileBuffer.h>

#include <Test/LSPTest.h>
#include <LSP/LSPMessages.h>

namespace eddy::test {

using namespace Obelix;
using namespace eddy::lsp;

TEST_F(LSPTest, GetTheLSP)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto std_err = lsp.process().standard_error();
    auto err = lsp.shutdown();
    EXPECT_FALSE(lsp.running());
}

TEST_F(LSPTest, EncodeInitializeParams)
{
    constexpr char const *URI = "file:///Users/jan/projects/Eddy/App";
    InitializeParams initialize_params;
    std::vector<WorkspaceFolder> folders { { .uri = URI, .name =  "App", } };
    initialize_params.workspaceFolders = folders;
    auto value = to_json(initialize_params);
    ASSERT_TRUE(value.has("workspaceFolders"));
    auto json_folders = *(value.get("workspaceFolders"));
    ASSERT_EQ(json_folders.type(), JSONType::Array);
    auto folder = *(json_folders.get(0));
    EXPECT_EQ(folder.get("uri")->to_string(), URI);
}

TEST_F(LSPTest, SendInitializeRequest)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto err = lsp.send_request<Initialize>(InitializeParams {});
    EXPECT_FALSE(err.is_error());
    auto& response = err.value();
    EXPECT_FALSE(response.is_error());
}

TEST_F(LSPTest, SendExitNotification)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto init_err = lsp.send_request<Initialize>(InitializeParams {});
    EXPECT_FALSE(init_err.is_error());
    auto err = lsp.send_notification<Exit>();
    EXPECT_FALSE(err.is_error());
}

TEST_F(LSPTest, SendShutdownRequest)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto init_err = lsp.send_request<Initialize>(InitializeParams {});
    EXPECT_FALSE(init_err.is_error());
    auto err = lsp.send_request<Shutdown>();
    EXPECT_FALSE(err.is_error());
}

TEST_F(LSPTest, SendDidOpenTextDocumentNotification)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    auto initialize_err = lsp.send_request<Initialize>(InitializeParams {});
    auto buffer = FileBuffer::from_file("/Users/jan/projects/Eddy/App/main.cpp");
    ASSERT_FALSE(buffer.is_error());
    DidOpenTextDocumentParams params;
    params.textDocument.text = buffer.value()->str();
    params.textDocument.languageId = "cpp";
    params.textDocument.uri = "file:///Users/jan/projects/Eddy/App/main.cpp";
    params.textDocument.version = 0;
    auto did_open_err = lsp.send_notification<TextDocumentDidOpen>(params);
    EXPECT_FALSE(did_open_err.is_error());
}

TEST_F(LSPTest, SendTextDocumentSemanticTokensFullRequest)
{
    auto& lsp = LSP::the();
    EXPECT_TRUE(lsp.running());
    InitializeParams initialize_params;
    std::vector<WorkspaceFolder> folders { { .uri =  "file:///Users/jan/projects/Eddy/App", .name =  "App", } };
    initialize_params.workspaceFolders = folders;
    auto initialize_err = lsp.send_request<Initialize>(initialize_params);
    auto buffer = FileBuffer::from_file("/Users/jan/projects/Eddy/App/main.cpp");
    ASSERT_FALSE(buffer.is_error());
    DidOpenTextDocumentParams params;
    params.textDocument.text = buffer.value()->str();
    params.textDocument.languageId = "cpp";
    params.textDocument.uri = "file:///Users/jan/projects/Eddy/App/main.cpp";
    params.textDocument.version = 0;
    auto did_open_err = lsp.send_notification<TextDocumentDidOpen>(params);
    EXPECT_FALSE(did_open_err.is_error());
    SemanticTokensParams semantic_tokens_params;
    semantic_tokens_params.textDocument.uri = "file:///Users/jan/projects/Eddy/App/main.cpp";
    auto semantic_tokens_err = lsp.send_request<TextDocumentSemanticTokensFull>(semantic_tokens_params);
    EXPECT_FALSE(semantic_tokens_err.is_error());
    if (semantic_tokens_err.is_error()) {
        std::cout << semantic_tokens_err.error().key;
        return;
    }
    auto const& semantic_tokens = semantic_tokens_err.value();
    ASSERT_FALSE(semantic_tokens.is_error());
    EXPECT_EQ(semantic_tokens.result().index(), 0);
}

} // Eddy::test
