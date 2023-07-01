/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <chrono>

#include "App/Document.h"
#include "Core/FileBuffer.h"
#include "Mode/Mode.h"

namespace eddy {

using namespace std::chrono_literals;
using namespace Obelix;

enum class LSPMessageType {
    Init,
    AllTokens,
    Edit,
    MultiEdit,
    Close,
};

struct LSPMessage {
    LSPMessageType type;
    std::variant<std::string,EditAction,std::vector<LSPMessage>,bool> data;
};

class CPlusPlus : public Mode {
public:
    CPlusPlus(Document& doc);
    ErrorOr<std::string_view, SystemError> open(fs::path const&);
    void parse();

private:
    void submit(LSPMessage msg);
    std::optional<LSPMessage> next_message();
    bool handle(LSPMessage const&);

    std::string m_uri;
    std::mutex m_queue_mutex;
    std::condition_variable m_condition;
    std::deque<LSPMessage> m_queue;
};

}
