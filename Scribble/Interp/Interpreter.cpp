/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <App/Scratch.h>
#include <Scribble/Interp/CommandAdapter.h>
#include <Scribble/Interp/Interpreter.h>
#include <Scribble/Interp/Value.h>
#include <Scribble/Interp/Function.h>
#include <Scribble/Scribble.h>

namespace scratch::interp {

using namespace Obelix;
using namespace scratch::scribble;

void StatementResult::log_message(std::string const& message)
{
    auto messages = split(message, '\n');
    for (auto msg_line : messages) {
        output.emplace_back(std::make_shared<StringBuffer>(msg_line));
    }
}

void StatementResult::clear()
{
    output.clear();
}

ProcessResult interpret(std::shared_ptr<Project> const& project, InterpreterContext& ctx)
{
    ProcessResult result;
    process(project, ctx, result);
    return result;
}

}

namespace scratch::scribble {

using namespace scratch::interp;

INIT_NODE_PROCESSOR(InterpreterContext)

NODE_PROCESSOR(Project)
{
    std::shared_ptr<Project> project = std::dynamic_pointer_cast<Project>(tree);

    std::shared_ptr<Module> main;
    std::shared_ptr<ExpressionResult> res;
    for (auto const& mod : project->modules()) {
        if (mod->name() == project->main_module()) {
            main = mod;
            continue;
        }
        res = TRY_AND_CAST(ExpressionResult, mod, ctx);
    }
    return TRY_AND_CAST(ExpressionResult, res, ctx);
}

NODE_PROCESSOR(Block)
{
    std::shared_ptr<Block> block = std::dynamic_pointer_cast<Block>(tree);

    std::shared_ptr<ExpressionResult> res;
    auto& block_ctx = make_subcontext(ctx);
    for (auto const& statement : block->statements()) {
        res = TRY_AND_CAST(ExpressionResult, statement, block_ctx);
        switch ((*block_ctx).type) {
        case StatementResult::StatementResultType::Return:
            return std::make_shared<ExpressionResult>(block->location(), (*block_ctx).payload);
        case StatementResult::StatementResultType::Break:
        case StatementResult::StatementResultType::Continue:
            return res;
        default:
            break;
        }
    }
    return res;
}

NODE_PROCESSOR(Module)
{
    std::shared_ptr<Module> mod = std::dynamic_pointer_cast<Module>(tree);

    std::shared_ptr<ExpressionResult> res;
    for (auto const& statement : mod->statements()) {
        res = TRY_AND_CAST(ExpressionResult, statement, ctx);
        switch ((*ctx).type) {
        case StatementResult::StatementResultType::Return:
            return std::make_shared<ExpressionResult>(mod->location(), (*ctx).payload);
        case StatementResult::StatementResultType::Break:
        case StatementResult::StatementResultType::Continue:
            return res;
        default:
            break;
        }
    }
    return res;
}


NODE_PROCESSOR(FunctionDef)
{
    auto func_def = std::dynamic_pointer_cast<FunctionDef>(tree);
    if (auto decl_maybe = ctx.declare(func_def->name(), Value { std::make_shared<ScribbleFunction>(func_def->name(), func_def) } ); decl_maybe.is_error())
        return decl_maybe.error();
    return std::make_shared<ExpressionResult>(func_def->location(), Value { });
}

NODE_PROCESSOR(ExpressionStatement)
{
    auto stmt = std::dynamic_pointer_cast<ExpressionStatement>(tree);
    auto expr = TRY_AND_CAST(ExpressionResult, stmt->expression(), ctx);
    return std::make_shared<ExpressionResult>(stmt->location(), expr->value());
}

NODE_PROCESSOR(VariableDeclaration)
{
    auto decl = std::dynamic_pointer_cast<VariableDeclaration>(tree);
    if (ctx.contains(decl->identifier()->name()))
        return SyntaxError { tree->location(), ErrorCode::VariableAlreadyDeclared };

    std::shared_ptr<ExpressionResult> expr;
    Value v;
    if (decl->expression() != nullptr) {
        expr = TRY_AND_CAST(ExpressionResult, decl->expression(), ctx);
        v = expr->value();
    } else {
        expr = std::make_shared<ExpressionResult>(decl->location(), v);
    }
    TRY_RETURN(ctx.declare(decl->identifier()->name(), v));
    return expr;
}

NODE_PROCESSOR(UnaryExpression)
{
    auto expr = std::dynamic_pointer_cast<UnaryExpression>(tree);
    auto operand = TRY_AND_CAST(ExpressionResult, expr->operand(), ctx);

    switch (expr->op().code()) {
    case TokenCode::Plus: {
        return operand;
    }
    case TokenCode::Minus: {
        auto res = operand->value().negate();
        if (res.is_error())
            return SyntaxError { expr->location(), *res.to_error() };
        return std::make_shared<ExpressionResult>(expr->location(), res);
    }
    case TokenCode::Tilde: {
        auto res = operand->value().bitwise_not();
        if (res.is_error())
            return SyntaxError { expr->location(), *res.to_error() };
        return std::make_shared<ExpressionResult>(expr->location(), res);
    }
    case TokenCode::ExclamationPoint: {
        auto res = operand->value().logical_not();
        if (res.is_error())
            return SyntaxError { expr->location(), *res.to_error() };
        return std::make_shared<ExpressionResult>(expr->location(), res);
    }
    default:
        return SyntaxError { expr->location(), "Unrecognized unary operator '{}'", expr->op() };
    }
}

template <typename Callback>
static ErrorOrNode calculate(pExpressionResult const& lhs, pExpressionResult const& rhs, ContextType& ctx, Callback const& callback)
{
    assert(rhs != nullptr);
    Value res = callback(lhs->value(), rhs->value());
    if (res.is_error())
        return SyntaxError { lhs->location(), *res.to_error() };
    return std::make_shared<ExpressionResult>(lhs->location(), res);
}

template <typename Callback>
static ErrorOrNode calculateAndAssign(pExpression const& lhs, pExpressionResult const& rhs, ContextType& ctx, Callback const& callback)
{
    assert(rhs != nullptr);
    auto ident = std::dynamic_pointer_cast<Identifier>(lhs);
    if (ident == nullptr)
        return SyntaxError { lhs->location(), ErrorCode::CannotAssignToRValue, lhs };
    auto value_maybe = ctx.get(ident->name());
    if (!value_maybe.has_value())
        return std::make_shared<ExpressionResult>(ident->location(), Value { ErrorCode::UndeclaredVariable });
    Value res = callback(value_maybe.value(), rhs->value());
    if (res.is_error())
        return SyntaxError { lhs->location(), *res.to_error() };
    ctx.set(ident->name(), res);
    return rhs;
}

NODE_PROCESSOR(BinaryExpression)
{
    auto expr = std::dynamic_pointer_cast<BinaryExpression>(tree);
    auto lhs = TRY_AND_TRY_CAST(ExpressionResult, expr->lhs(), ctx);
    auto rhs_node = TRY_AND_CAST(SyntaxNode, expr->rhs(), ctx);
    auto rhs = std::dynamic_pointer_cast<ExpressionResult>(rhs_node);

    switch (expr->op().code()) {
    case TokenCode::Equals: {
        auto ident = std::dynamic_pointer_cast<Identifier>(expr->lhs());
        if (ident == nullptr)
            return SyntaxError { expr->location(), ErrorCode::CannotAssignToRValue, expr->lhs() };
        ctx.set(ident->name(), rhs->value());
        return rhs;
    }

    case Scribble::KeywordIncEquals: {
        return calculateAndAssign(expr->lhs(), rhs, ctx,
            [](Value const& l, Value const& r) { return l.add(r); });
    }

    case Scribble::KeywordDecEquals: {
        return calculateAndAssign(expr->lhs(), rhs, ctx,
            [](Value const& l, Value const& r) { return l.subtract(r); });
    }

    case Scribble::KeywordMultEquals: {
        return calculateAndAssign(expr->lhs(), rhs, ctx,
            [](Value const& l, Value const& r) { return l.multiply(r); });
    }

    case Scribble::KeywordDivEquals: {
        return calculateAndAssign(expr->lhs(), rhs, ctx,
            [](Value const& l, Value const& r) { return l.multiply(r); });
    }

    case Scribble::KeywordModEquals: {
        return calculateAndAssign(expr->lhs(), rhs, ctx,
            [](Value const& l, Value const& r) { return l.modulo(r); });
    }

    case Scribble::KeywordBitwiseOrEquals: {
        return calculateAndAssign(expr->lhs(), rhs, ctx,
            [](Value const& l, Value const& r) { return l.bitwise_or(r); });
    }

    case Scribble::KeywordBitwiseAndEquals: {
        return calculateAndAssign(expr->lhs(), rhs, ctx,
            [](Value const& l, Value const& r) { return l.bitwise_and(r); });
    }

    case Scribble::KeywordBitwiseXorEquals: {
        return calculateAndAssign(expr->lhs(), rhs, ctx,
            [](Value const& l, Value const& r) { return l.bitwise_xor(r); });
    }

    case Scribble::KeywordShlEquals: {
        return calculateAndAssign(expr->lhs(), rhs, ctx,
            [](Value const& l, Value const& r) { return l.shift_left(r); });
    }

    case Scribble::KeywordShrEquals: {
        return calculateAndAssign(expr->lhs(), rhs, ctx,
            [](Value const& l, Value const& r) { return l.shift_right(r); });
    }

    case TokenCode::OpenParen: {
        if (lhs->value().is_error())
            return SyntaxError { expr->location(), *lhs->value().to_error(), expr->lhs() };
        if (!lhs->value().is_function())
            return SyntaxError { expr->location(), ErrorCode::FunctionUndefined, expr->lhs() };
        Values args;
        if (rhs_node->node_type() == SyntaxNodeType::ExpressionResultList) {
            args = std::dynamic_pointer_cast<ExpressionResultList>(rhs_node)->values();
        } else {
            args = { rhs->value() };
        }
        auto f = *(lhs->value().to_function());
        return std::make_shared<ExpressionResult>(expr->location(), f->execute(args, ctx));
    }

    case TokenCode::Plus: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.add(rhs); });
    };

    case TokenCode::Minus: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.subtract(rhs); });
    };

    case TokenCode::Asterisk: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.multiply(rhs); });
    };

    case TokenCode::Slash: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.divide(rhs); });
    };

    case TokenCode::Percent: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.modulo(rhs); });
    };

    case TokenCode::LogicalOr: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.logical_or(rhs); });
    };

    case TokenCode::LogicalAnd: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.logical_and(rhs); });
    };

    case TokenCode::Pipe: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.bitwise_or(rhs); });
    };

    case TokenCode::Ampersand: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.bitwise_and(rhs); });
    };

    case TokenCode::Hat: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.bitwise_xor(rhs); });
    };

    case TokenCode::ShiftLeft: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.shift_left(rhs); });
    };

    case TokenCode::ShiftRight: {
        return calculate(lhs, rhs, ctx, [](Value const& lhs, Value const& rhs) { return lhs.shift_right(rhs); });
    };

    case TokenCode::EqualsTo: {
        auto res = Value(lhs->value() == rhs->value());
        return std::make_shared<ExpressionResult>(expr->location(), res);
    };

    case TokenCode::NotEqualTo: {
        auto res = Value(lhs->value() != rhs->value());
        return std::make_shared<ExpressionResult>(expr->location(), res);
    }

    case TokenCode::GreaterThan: {
        auto res = Value(lhs->value() > rhs->value());
        return std::make_shared<ExpressionResult>(expr->location(), res);
    };

    case TokenCode::GreaterEqualThan: {
        auto res = Value(lhs->value() >= rhs->value());
        return std::make_shared<ExpressionResult>(expr->location(), res);
    };

    case TokenCode::LessThan: {
        auto res = Value(lhs->value() < rhs->value());
        return std::make_shared<ExpressionResult>(expr->location(), res);
    };

    case TokenCode::LessEqualThan: {
        auto res = Value(lhs->value() <= rhs->value());
        return std::make_shared<ExpressionResult>(expr->location(), res);
    };

    case Scribble::KeywordRange: {
        if (lhs->value().type() != ValueType::Integer || rhs->value().type() != ValueType::Integer)
            return SyntaxError { expr->location(), ErrorCode::TypeMismatch };
        return std::make_shared<ExpressionResultList>(expr->location(), Values { lhs->value(), rhs->value() });
    }

    default:
        return SyntaxError { expr->location(), "Unrecognized binary operator '{}'", expr->op() };
    }
}

NODE_PROCESSOR(Variable)
{
    auto ident = std::dynamic_pointer_cast<Identifier>(tree);
    auto value_maybe = ctx.get(ident->name());
    if (!value_maybe.has_value())
        value_maybe = ErrorCode::UndeclaredVariable;
    return std::make_shared<ExpressionResult>(ident->location(), value_maybe.value());
}

NODE_PROCESSOR(IntLiteral)
{
    auto literal = std::dynamic_pointer_cast<IntLiteral>(tree);
    return std::make_shared<ExpressionResult>(literal->location(), Value(token_value<long>(literal->token()).value()));
}

NODE_PROCESSOR(StringLiteral)
{
    auto literal = std::dynamic_pointer_cast<StringLiteral>(tree);
    return std::make_shared<ExpressionResult>(literal->location(), Value(literal->string()));
}

NODE_PROCESSOR(ExpressionList)
{
    auto list = std::dynamic_pointer_cast<ExpressionList>(tree);
    Values values;
    for (auto const& expr : list->expressions()) {
        auto value = TRY_AND_CAST(ExpressionResult, expr, ctx);
        if (value->value().is_error())
            return SyntaxError { expr->location(), *value->value().to_error() };
        values.push_back(value->value());
    }
    return std::make_shared<ExpressionResultList>(list->location(), values);
}

NODE_PROCESSOR(IfStatement)
{
    auto if_stmt = std::dynamic_pointer_cast<IfStatement>(tree);
    for (auto const& branch : if_stmt->branches()) {
        auto cond = TRY_AND_CAST(ExpressionResult, branch->condition(), ctx);

        if (auto match_maybe = cond->value().to_bool(); match_maybe) {
            if (*match_maybe)
                return TRY_AND_CAST(ExpressionResult, branch->statement(), ctx);
        } else {
            return SyntaxError { if_stmt->location(), ErrorCode::TypeMismatch };
        }
    }
    if (if_stmt->else_stmt() != nullptr)
        return TRY_AND_CAST(ExpressionResult, if_stmt->else_stmt(), ctx);
    return std::make_shared<ExpressionResult>(if_stmt->location(), Value {});
}

NODE_PROCESSOR(SwitchStatement)
{
    auto switch_stmt = std::dynamic_pointer_cast<SwitchStatement>(tree);
    for (auto const& case_stmt : switch_stmt->cases()) {
        auto match_expr = std::make_shared<BinaryExpression>(switch_stmt->expression(), Token { {}, TokenCode::EqualsTo, "==" }, case_stmt->condition());
        auto match_value = TRY_AND_CAST(ExpressionResult, match_expr, ctx);
        if (auto match_maybe = match_value->value().to_bool(); match_maybe) {
            if (*match_maybe)
                return TRY_AND_CAST(ExpressionResult, case_stmt->statement(), ctx);
        } else {
            return SyntaxError { case_stmt->location(), ErrorCode::TypeMismatch };
        }
    }
    if (switch_stmt->default_case() != nullptr)
        return TRY_AND_CAST(ExpressionResult, switch_stmt->default_case()->statement(), ctx);
    return std::make_shared<ExpressionResult>(switch_stmt->location(), Value {});
}

NODE_PROCESSOR(ExpressionResult)
{
    return tree;
}

NODE_PROCESSOR(WhileStatement)
{
    auto while_stmt = std::dynamic_pointer_cast<WhileStatement>(tree);

    Value res;
    do {
        auto cond = TRY_AND_CAST(ExpressionResult, while_stmt->condition(), ctx);
        auto cond_maybe = cond->value().to_bool();
        if (!cond_maybe)
            return SyntaxError { while_stmt->location(), ErrorCode::TypeMismatch };
        if (!cond_maybe.value())
            return std::make_shared<ExpressionResult>(while_stmt->location(), res);
        auto stmt_result = TRY_AND_CAST(ExpressionResult, while_stmt->statement(), ctx);
        if ((*ctx).type == StatementResult::StatementResultType::Break)
            return std::make_shared<ExpressionResult>(while_stmt->location(), res);
        if ((*ctx).type == StatementResult::StatementResultType::Return) {
            return std::make_shared<ExpressionResult>(while_stmt->location(), (*ctx).payload);
        }
        res = stmt_result->value();
    } while (true);
}

NODE_PROCESSOR(ForStatement)
{
    auto for_stmt = std::dynamic_pointer_cast<ForStatement>(tree);

    Value res;
    auto range_expr = TRY_AND_CAST(ExpressionResultList, for_stmt->range(), ctx);
    auto current = *(range_expr->values()[0].to_int<long>());
    auto upper_bound = *(range_expr->values()[1].to_int<long>());
    InterpreterContext& for_ctx = make_subcontext(ctx);
    TRY_RETURN(for_ctx.declare(for_stmt->variable()->name(), Value(current)));
    while (current < upper_bound) {
        for_ctx.set(for_stmt->variable()->name(), Value(current));
        auto stmt_result = TRY_AND_CAST(ExpressionResult, for_stmt->statement(), for_ctx);
        if ((*for_ctx).type == StatementResult::StatementResultType::Break)
            break;
        if ((*for_ctx).type == StatementResult::StatementResultType::Return) {
            ctx = *for_ctx;
            return std::make_shared<ExpressionResult>(for_stmt->location(), (*ctx).payload);
        }
        res = stmt_result->value();
        ++current;
    }
    return std::make_shared<ExpressionResult>(for_stmt->location(), res);
}

NODE_PROCESSOR(Return)
{
    auto ret_stmt = std::dynamic_pointer_cast<Return>(tree);
    if (ret_stmt->expression()) {
        auto ret_val = TRY_AND_CAST(ExpressionResult, ret_stmt->expression(), ctx);
        *ctx = { StatementResult::StatementResultType::Return, ret_val->value() };
    } else {
        *ctx = { StatementResult::StatementResultType::Return, Value {} };
    }
    return std::make_shared<ExpressionResult>(ret_stmt->location(), (*ctx).payload);
}

NODE_PROCESSOR(Break)
{
    *ctx = { StatementResult::StatementResultType::Break, Value {} };
    return std::make_shared<ExpressionResult>(tree->location(), Value {});
}

NODE_PROCESSOR(Continue)
{
    *ctx = { StatementResult::StatementResultType::Continue, Value {} };
    return std::make_shared<ExpressionResult>(tree->location(), Value {});
}

}
