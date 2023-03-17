/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Scribble/Context.h>
#include <Scribble/Interp/ExpressionResult.h>
#include <Scribble/Processor.h>
#include <Scribble/Syntax/Statement.h>

namespace Scratch::Interp {

using namespace Obelix;

struct StatementResult {
    enum class StatementResultType {
        None,
        Error,
        Break,
        Continue,
        Return,
    };
    StatementResultType type { StatementResultType::None };
    Value payload {};
    std::vector<std::shared_ptr<StringBuffer>> output;

    StatementResult& operator=(StatementResult const&) = default;

    void log_message(std::string const&);
    void clear();
};

using InterpreterContext = Context<Value, StatementResult>;

[[nodiscard]] ProcessResult interpret(std::shared_ptr<Project> const&, InterpreterContext&);

[[nodiscard]] inline ProcessResult interpret(std::shared_ptr<Project> const& project, std::function<ErrorOr<void,SyntaxError>(InterpreterContext&)> const& initializer)
{
    InterpreterContext ctx;
    if (auto error_maybe = initializer(ctx); error_maybe.is_error()) {
        return ProcessResult { error_maybe.error() };
    }
    return interpret(project, ctx);
}

[[nodiscard]] inline ProcessResult interpret(std::shared_ptr<Project> const& project)
{
    InterpreterContext ctx;
    return interpret(project, ctx);
}

}
