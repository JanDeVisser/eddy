/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <future>
#include <set>

#include <core/Error.h>
#include <core/Process.h>

#include <LSP/JSON.h>
#include <LSP/Message.h>
#include <LSP/LSPMessages.h>

namespace scratch::lsp {

using namespace Obelix;

ErrorOr<void,SystemError> start();

class LSP {
public:
    static LSP& the();
    bool running() const;
    [[nodiscard]] Process& process();
    ErrorOr<void, SystemError> shutdown();
    ErrorOr<void, SystemError> send(JSONValue const& value);
    ErrorOr<JSONValue, SystemError> receive();
    [[nodiscard]] ServerCapabilities const& server_capabilities() { return m_serverCapabilities; }
    [[nodiscard]] std::string const& server_name() { return m_serverName; }
    [[nodiscard]] std::string const& server_version() { return m_serverVersion; }

    [[nodiscard]] std::set<SemanticTokenModifiers> token_type_modifiers(int modifiers)
    {
        std::set<SemanticTokenModifiers> ret;
        for (auto ix = 0u; ix < m_token_type_modifiers.size(); ++ix) {
            if (modifiers & (1 << ix))
                ret.insert(m_token_type_modifiers[ix]);
        }
        return ret;
    }

    [[nodiscard]] SemanticTokenTypes token_type(int type)
    {
        if ((type >= 0) && (type < m_token_type_legend.size()))
            return m_token_type_legend[type];
        return SemanticTokenTypes::Variable;
    }

    template <class RequestClass>
    ErrorOr<Response<typename RequestClass::ResultClass>, JSONDecodeError> send_request(typename RequestClass::ParameterClass params)
    {
        RequestClass req { std::move(params) };
        return send_request(req);
    }

    template <class RequestClass>
    ErrorOr<Response<typename RequestClass::ResultClass>, JSONDecodeError> send_request()
    {
        RequestClass req;
        return send_request(req);
    }

    template <class NotificationClass>
    ErrorOr<void, JSONDecodeError> send_notification(typename NotificationClass::ParameterClass params)
    {
        NotificationClass notification { std::move(params) };
        return send_notification(notification);
    }

    template <class NotificationClass>
    ErrorOr<void, JSONDecodeError> send_notification()
    {
        NotificationClass notification;
        return send_notification(notification);
    }

    std::promise<JSONValue>* promise_for(int id)
    {
        std::unique_lock const lock(m_promises_guard);
        if (m_promises.contains(id)) {
            return m_promises.at(id);
        }
        return nullptr;
    }

    void register_promise(int id, std::promise<JSONValue>* promise)
    {
        std::unique_lock const lock(m_promises_guard);
        m_promises[id] = promise;
    }

    void drop_promise(int id)
    {
        std::unique_lock const lock(m_promises_guard);
        if (m_promises.contains(id)) {
            m_promises.erase(id);
        }
    }

private:
    LSP();
    static LSP s_lsp;
    ServerCapabilities m_serverCapabilities;
    std::string m_serverName;
    std::string m_serverVersion;
    std::optional<SemanticTokensLegend> m_semanticTokenLegend {};
    std::vector<SemanticTokenTypes> m_token_type_legend;
    std::vector<SemanticTokenModifiers> m_token_type_modifiers;

    Process m_process;
    std::mutex m_promises_guard;
    std::map<int,std::promise<JSONValue>*> m_promises;

    void initialize();

    template <class RequestClass>
    ErrorOr<Response<typename RequestClass::ResultClass>, JSONDecodeError> send_request(RequestClass const& request)
    {
        std::promise<JSONValue> promise;
        auto future { promise.get_future() };

        register_promise(request.id(), &promise);
        auto err_maybe = send(to_json<RequestClass>(request));
        if (err_maybe.is_error())
            return JSONDecodeError { JSONDecodeError::Code::ProtocolError, err_maybe.error().to_string() };
        future.wait();
        drop_promise(request.id());
        auto response = future.get();

        auto result = TRY(decode_response<RequestClass>(response));
        if (result.id() != request.id()) {
            return JSONDecodeError { JSONDecodeError::Code::UnexpectedValue, "id" };
        }
        return result;
    }

    template <class NotificationClass>
    ErrorOr<void, JSONDecodeError> send_notification(NotificationClass const& notification)
    {
        auto ret_maybe = send(to_json<NotificationClass>(notification));
        if (ret_maybe.is_error())
            return JSONDecodeError { JSONDecodeError::Code::ProtocolError, ret_maybe.error().to_string() };
        return {};
    }

};

}
