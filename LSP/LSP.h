/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <core/Error.h>
#include <core/Process.h>

#include <LSP/JSON.h>

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

private:
    LSP();
    static LSP s_lsp;
    Process m_process;
};

}
