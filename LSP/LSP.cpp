/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <core/Logging.h>

#include <LSP/LSP.h>

namespace scratch::lsp {

using namespace std::literals;

LSP LSP::s_lsp;

LSP& LSP::the()
{
    if (!s_lsp.m_process.running()) {
        if (auto err = s_lsp.m_process.background(); err.is_error())
            fatal("Could not start LSP client: {}", err.error().to_string());
        std::thread thread { []() {
            while (s_lsp.running()) {
                auto msg_maybe = s_lsp.receive();
                if (msg_maybe.is_error()) {
                    std::cout << msg_maybe.error().to_string();
                    continue;
                }
                auto const& msg = msg_maybe.value();
                if (msg.has("id")) {
                    auto id = *(msg["id"].to_int<int>());
                    auto promise = s_lsp.promise_for(id);
                    if (promise != nullptr) {
                        promise->set_value(msg);
                    }
                }
            }
        } };
        thread.detach();
    }
    return s_lsp;
}

LSP::LSP()
    : m_process("/usr/bin/clangd", "--log=info", "--input-mirror-file=jj")
{
}

bool LSP::running() const
{
    return m_process.running();
}

Process& LSP::process()
{
    return m_process;
}

ErrorOr<void, SystemError> LSP::shutdown()
{
    return m_process.terminate();
}

ErrorOr<void, SystemError> LSP::send(JSONValue const& value)
{
    std::string json = value.serialize();
    std::string message = format(
    R"(Content-Length: {}
Content-Type: application/vscode-jsonrpc; charset=utf-8

{}
)", json.length() + 1, json);
    TRY_RETURN(m_process.write(message));
    return {};
}

ErrorOr<JSONValue, SystemError> LSP::receive()
{
    m_process.out().expect();
    auto msg = m_process.standard_out();

    long len = -1;
    bool in_header { true };
    std::string json;
    for (auto const& line : msg) {
        if (in_header) {
            if (line.empty()) {
                in_header = false;
                continue;
            }
            if (line.starts_with("Content-Type:"))
                continue;
            if (line.starts_with("Content-Length: ")) {
                auto len_as_str = line.substr("Content-Length: "sv.length());
                auto len_maybe = try_to_long<std::string>()(len_as_str);
                if (!len_maybe.value())
                    return SystemError { ErrorCode::TypeMismatch, "Could not convert Content-Length: {} to integer", len_as_str };
                len = *len_maybe;
                continue;
            }
            return SystemError { ErrorCode::SyntaxError, "Unknown header '{}'", line };
        }
        if (len < 0)
            return SystemError { ErrorCode::SyntaxError, "No Content-Length: specified" };
        if (!json.empty())
            json += "\n";
        json += line;
    }
    auto value_maybe = JSONValue::deserialize(json);
    if (!value_maybe.has_value())
        return SystemError { ErrorCode::SyntaxError, "Unparseable message" };
    return *value_maybe;
}

}
