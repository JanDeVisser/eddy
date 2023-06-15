/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Scribble/Interp/Interpreter.h>
#include <Scribble/Interp/Value.h>
#include <Scribble/Syntax/Function.h>

namespace eddy::interp {

class Function {
public:
    Function(std::string);
    virtual ~Function() = default;
    std::string const& name() const;
    [[nodiscard]] virtual Value execute(std::vector<Value> const&, InterpreterContext&) const = 0;
    [[nodiscard]] virtual std::string to_string() const;
private:
    std::string m_name;
};

using pFunction = std::shared_ptr<Function>;

class ScribbleFunction : public Function {
public:
    ScribbleFunction(std::string, pFunctionDef);
    [[nodiscard]] Value execute(std::vector<Value> const&, InterpreterContext&) const override;
    [[nodiscard]] pFunctionDef const& function() const;

private:
    pFunctionDef m_function;
};

template <typename BuiltInImpl>
class BuiltIn : public Function {
public:
    BuiltIn(std::string name, BuiltInImpl const& impl)
        : Function(std::move(name))
        , m_impl(impl)
    {
    }

    Value execute(std::vector<Value> const& args, InterpreterContext& ctx) const override
    {
        return m_impl(args, ctx);
    }

private:
    BuiltInImpl const& m_impl;
};

template <typename BuiltInImpl>
inline ErrorOr<void, SyntaxError> register_builtin(InterpreterContext& ctx, std::string const& name, BuiltInImpl const& impl)
{
    TRY_RETURN(ctx.declare(name, Value { std::make_shared<BuiltIn<BuiltInImpl>>(name, impl) } ));
    return {};
}

}
