/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Scribble/Interp/Function.h>
#include <Scribble/Interp/Value.h>
#include <Widget/Command.h>

namespace scratch::interp {

class CommandAdapter : public Function {
public:
    CommandAdapter(std::string, ScheduledCommand const&);
    Value execute(std::vector<Value> const&, InterpreterContext&) const override;
private:
    ScheduledCommand const& m_command;
};

} // Scratch::Interp
