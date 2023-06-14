/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <core/FileBuffer.h>
#include <LSP/LSP.h>
#include <LSP/LSPMessages.h>
#include <Mode/CPlusPlus.h>

namespace scratch {

using namespace Obelix;
using namespace scratch::lsp;

CPlusPlus::CPlusPlus(Document& doc)
    : Mode(doc)
{
    std::thread thread {
        [this]() {
            while (true) {
                std::vector<LSPMessage> edits;
                auto msg_maybe = next_message();
                while (msg_maybe && (*msg_maybe).type == LSPMessageType::Edit) {
                    edits.push_back(*msg_maybe);
                    msg_maybe = next_message();
                }
                LSPMessage msg;
                if (!edits.empty()) {
                    msg.type = LSPMessageType::MultiEdit;
                    msg.data = edits;
                }

                std::unique_lock lock(m_queue_mutex);
                while (!m_queue.empty()) {
                    auto msg = m_queue.front();
                    m_queue.pop_front();
                    switch (msg.type) {
                    case LSPMessageType::Init:
                        // Split and add to lines vector
                        // Initiate TextDocumentSemanticTokensFull request
                        // handle and colorize lines
                        break;
                    case LSPMessageType::Edit:
                        // Collect all messages
                    }
                    if (!handle(msg))
                        return;
                }
                m_condition.wait(lock);
            }
        }
    };
    thread.detach();
    assign_text = [](std::string_view text) {};
    parse_text = [](Document& doc) {};
}

void CPlusPlus::submit(LSPMessage msg)
{
    std::lock_guard const lock(m_queue_mutex);
    m_queue.push_back(std::move(msg));
    m_condition.notify_all();
}

std::optional<LSPMessage> CPlusPlus::next_message()
{
    std::unique_lock lock(m_queue_mutex);
    while (true) {
        if (!m_queue.empty()) {
            auto msg = m_queue.front();
            m_queue.pop_front();
            return msg;
        }
        m_condition.wait_for(lock, 200ms);
        if (m_queue.empty())
            return {};
    }
    fatal("Unreachable");
}

bool CPlusPlus::handle(LSPMessage const& msg)
{
    switch (msg.type) {
    case LSPMessageType::MultiEdit: {
        auto edits = std::get<std::vector<LSPMessage>>(msg.data);
        return std::all_of(edits.begin(), edits.end(), [this](auto const& m) -> bool { return handle(m); });
    }
    case LSPMessageType::Init: {
        DidOpenTextDocumentParams params;
        params.textDocument.text = document().text();
        params.textDocument.languageId = "cpp";
        params.textDocument.uri = m_uri;
        params.textDocument.version = 0;
        if (auto is_err = LSP::the().send_notification<TextDocumentDidOpen>(params); is_err.is_error()) {
            // FIXME log to console
            std::cout << "Error in LSP comms: " << is_err.error().key << "\n";
        }
        return true;
    }
    case LSPMessageType::AllTokens: {
        auto& lsp = LSP::the();
        SemanticTokensParams semantic_tokens_params;
        semantic_tokens_params.textDocument.uri = m_uri;
        auto semantic_tokens_err = lsp.send_request<TextDocumentSemanticTokensFull>(semantic_tokens_params);
        if (semantic_tokens_err.is_error()) {
            std::cout << "Error in LSP comms: " << semantic_tokens_err.error().key << "\n";
            return true;
        }
        assert(!semantic_tokens_err.is_error());
        auto semantic_tokens_result = semantic_tokens_err.value().result();
        if (semantic_tokens_result.index() != 0) {
            std::cout << "Error in LSP comms: TextDocumentSemanticTokensFull returns no tokens" << "\n";
            return true;
        }
        auto semantic_tokens = std::get<SemanticTokens>(semantic_tokens_result).data;
        auto line = -1;
        auto col = 0;
        std::string text;
        for (auto ix = 0; ix <=  semantic_tokens.size() - 5; ix += 5) {
            auto line_delta = semantic_tokens[ix];
            auto col_delta = semantic_tokens[ix+1];
            auto len = semantic_tokens[ix+2];
            auto token_type = semantic_tokens[ix+3];
            auto modifiers = semantic_tokens[ix+4];

            auto new_line = line;
            if (line_delta > 0) {
                new_line += line_delta;
            } else if (new_line < 0) {
                new_line = 0;
            }
            if (new_line != line) {
                text = m_doc.line(new_line);
            }
        }
        return true;
    }
    case LSPMessageType::Edit:
        return true;
    case LSPMessageType::Close:
        return false;
    }
}


void CPlusPlus::parse(Document& doc)
{
    auto& lsp = LSP::the();
    SemanticTokensParams semantic_tokens_params;
    semantic_tokens_params.textDocument.uri = m_uri;
    auto semantic_tokens_err = lsp.send_request<TextDocumentSemanticTokensFull>(semantic_tokens_params);
    assert(!semantic_tokens_err.is_error());
    auto semantic_tokens_result = semantic_tokens_err.value().result();
    if (semantic_tokens_result.index() != 0)
        return;
    auto semantic_tokens = std::get<SemanticTokens>(semantic_tokens_result);
}

}
