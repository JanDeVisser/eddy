/**
 * Copyright (c) 2024, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 *
 * THIS IS GENERATED CODE. DO NOT MODIFY.
 */

#pragma once

#include <LSP/Schema/LSPBase.h>

namespace LSP {

struct WorkDoneProgressParams : public LSPObject {

    static Result<WorkDoneProgressParams, JSONError> decode(JSONValue const &json)
    {
        WorkDoneProgressParams ret;
        return ret;
    }

    JSONValue encode()
    {
        JSONValue ret;
    };
};

} /* namespace LSP */
