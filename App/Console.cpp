/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <App/Console.h>
#include <App/Editor.h>
#include <App/Scratch.h>
#include <Parser/Scribble.h>
#include <Widget/App.h>
#include <Scribble/Parser.h>
#include <Scribble/Scribble.h>
#include <Scribble/Interp/CommandAdapter.h>
#include <Scribble/Syntax/Literal.h>

namespace scratch {

using namespace scratch::scribble;

ErrorOr<void, SyntaxError> register_command(InterpreterContext& ctx, std::string const& command, Widget& widget)
{
    auto cmd = widget.command(command);
    if (!cmd)
        return SyntaxError { {}, "Unknown command {}", command };
    TRY_RETURN(ctx.declare(command,
        Value { std::make_shared<CommandAdapter>(command, *cmd) } ));
    return {};
}

ErrorOr<void, SyntaxError> initialize_context(InterpreterContext& ctx)
{
    TRY_RETURN(register_command(ctx, "set-fixed-width-font", Scratch::scratch()));

    TRY_RETURN(register_builtin(ctx, "console-log",
        [](Values const& args, InterpreterContext& ctx) -> Value {
            for (auto const& msg : args) {
                ctx.data().log_message(msg.to_string());
            }
            return Value {};
        }));
    TRY_RETURN(register_builtin(ctx, "string-length",
        [](Values const& args, InterpreterContext&) -> Value {
            if (args.empty() || args.size() > 1)
                return Value { ErrorCode::ArgumentCountMismatch };
            if (args[0].type() != ValueType::Text)
                return Value { ErrorCode::ArgumentTypeMismatch };
            return Value { args[0].to_string().length() };
        }));
    return {};
}

void ConsoleStatement::compile(std::string const& statement)
{
    text = std::make_shared<StringBuffer>(statement);
    node = nullptr;
    result = Value {};
    lines.clear();
    lines.emplace_back();
    lines.back().start_index = 0;
    auto length = 0u;
    if (text->buffer().empty()) {
        lines.back().tokens.emplace_back(Span {}, Scribble::OKPrompt, "*> ");
        return;
    }
    auto project_maybe = compile_project("**Console**", text);
    TokenCode prompt = Scribble::ErrorPrompt;
    if (project_maybe.has_value()) {
        auto project = std::dynamic_pointer_cast<Project>(project_maybe.value());
        node = project;
        if (project->is_complete()) {
            prompt = Scribble::OKPrompt;
        }
    }
    lines.back().tokens.emplace_back(Span {}, prompt, "*> ");
    auto const& tokens = (node) ? node->modules()[0]->tokens() : project_maybe.tokens();
    for (auto const& token : tokens) {
        if (token.code() == TokenCode::EndOfFile)
            break;
        switch (token.code()) {
        case TokenCode::NewLine:
            length += 1;
            lines.emplace_back();
            prompt = Scribble::ContinuationPrompt;
            lines.back().start_index = static_cast<int>(length);
            lines.back().tokens.emplace_back(Span {}, Scribble::ContinuationPrompt, "-> ");
            break;
        default:
            lines.back().tokens.push_back(token);
            length += token.value().length();
            break;
        }
    }
    for (auto const& error : project_maybe.errors()) {
        std::cout << "ERROR: " + error.to_string() + "\n";
    }
}

void ConsoleStatement::execute(InterpreterContext& ctx)
{
    assert(node && node->is_complete());
    auto interpret_result = interpret(node, ctx);
    if (interpret_result.is_error()) {
        result = interpret_result.error().to_string();
        lines.emplace_back();
        lines.back().start_index = -1;
        lines.back().tokens.emplace_back(Span {}, TokenCode::Error, interpret_result.error().to_string());
    } else {
        for (auto const& output_line : ctx.data().output) {
            output.emplace_back(output_line);
            lines.emplace_back();
            lines.back().start_index = -1;
            lines.back().tokens.emplace_back(Span {}, Scribble::OutputLine, output_line->str());
        }
        auto r = std::dynamic_pointer_cast<interp::ExpressionResult>(interpret_result.value());
        result = r->value();
        if (!r->value().is_null()) {
            lines.emplace_back();
            lines.back().start_index = -1;
            lines.back().tokens.emplace_back(Span {}, Scribble::ExecutionResult, r->value().to_string());
        }
    }
}

ConsoleCommands::ConsoleCommands()
{
}

ConsoleCommands Console::s_console_commands;

Console::Console(Editor* editor)
    : Buffer(editor)
{
    m_commands = &s_console_commands;
    if (auto err_maybe = initialize_context(m_ctx); err_maybe.is_error()) {
        fatal("Error initializing interpreter context: {}", err_maybe.error());
    }
    m_current.lines.emplace_back();
    m_current.lines.back().tokens.emplace_back(Span {}, Scribble::OKPrompt, "*> ");
}

void Console::render()
{
    size_t lines { 0 };
    if (!m_statements.empty())
        lines = m_statements.back().line + m_statements.back().lines.size();
    lines += m_current.lines.size();
    size_t top_line = (lines > editor()->rows()) ? lines - editor()->rows() : 0;

    auto render_statement = [this](ConsoleStatement const& stmt, size_t first_line) -> void {
        for (auto ix = first_line; ix < stmt.lines.size(); ++ix) {
            auto l = stmt.lines[ix];
            auto len = 0u;
            for (auto const& token : l.tokens) {
                auto t = token.value();
                if (len + t.length() < m_screen_left) {
                    len += t.length();
                    continue;
                } else if (len < m_screen_left) {
                    t = t.substr(m_screen_left - len);
                } else if (len + t.length() > m_screen_left + columns()) {
                    t = t.substr(0, m_screen_left + columns() - len);
                }
                editor()->append(scratch::parser::ScribbleParser::token_for(token.code(), t));
                len += token.value().length();
                if (len >= m_screen_left + editor()->columns())
                    break;
            }
            editor()->newline();
        }
    };

    size_t row = 0;
    size_t next_line = 0;
    for (auto const& stmt : m_statements) {
        next_line += stmt.line + stmt.lines.size() + 1;
        if (stmt.line + stmt.lines.size() + 1 < top_line)
            continue;
        render_statement(stmt, (stmt.line >= top_line) ? 0 : top_line - stmt.line);
        row += stmt.lines.size();
    }
    render_statement(m_current, (next_line >= top_line) ? 0 : top_line - next_line);
    editor()->text_cursor(static_cast<int>(row + m_cursor_line), static_cast<int>(m_cursor_column + 3 - m_screen_left));
}

bool Console::dispatch(SDL_Keysym sym)
{
    std::string statement;
    if (m_current.text != nullptr)
        statement = m_current.text->str();
    switch (sym.sym) {
    case SDLK_RETURN: {
        if (m_current.node != nullptr && m_current.node->is_complete()) {
            execute();
        } else {
            statement.insert(m_cursor, "\n");
            m_cursor_column = 0;
            m_cursor_line++;
            m_cursor++;
            compile(statement);
        }
        return true;
    };
    case SDLK_LEFT: {
        if (m_cursor_column > 0) {
            m_cursor_column--;
            m_cursor--;
            m_screen_left = clamp(m_screen_left, std::max(0ul, m_cursor_column - editor()->columns() + 1), m_cursor_column);
        }
        return true;
    }
    case SDLK_RIGHT: {
        if (m_cursor_column < m_current.lines[m_cursor_line].length() - 3) {
            m_cursor_column++;
            m_cursor++;
            m_screen_left = clamp(m_screen_left, std::max(0ul, m_cursor_column - editor()->columns() + 1), m_cursor_column);
        }
        return true;
    }
    case SDLK_DOWN: {
        if ((m_current.lines.size() > (m_cursor_line + 1)) && (m_current.lines[m_cursor_line].start_index >= 0)) {
            m_cursor_line++;
            m_cursor = clamp(static_cast<int>(m_current.lines[m_cursor_line].start_index + m_cursor_column),
                m_current.lines[m_cursor_line].start_index,
                static_cast<int>(m_current.lines[m_cursor_line].start_index + m_current.lines[m_cursor_line].length() - 3));
            m_cursor_column = clamp(m_cursor_column, 0ul, m_current.lines[m_cursor_line].length() - 3);
        }
        return true;
    }
    case SDLK_UP: {
        if (m_cursor_line > 0) {
            m_cursor_line--;
            m_cursor = clamp(static_cast<int>(m_current.lines[m_cursor_line].start_index + m_cursor_column),
                m_current.lines[m_cursor_line].start_index,
                static_cast<int>(m_current.lines[m_cursor_line].start_index + m_current.lines[m_cursor_line].length() - 3));
            m_cursor_column = clamp(m_cursor_column, 0ul, m_current.lines[m_cursor_line].length() - 3);
        }
        return true;
    }
    case SDLK_HOME:
        m_cursor_column = 0;
        m_cursor = m_current.lines[m_cursor_line].start_index;
        return true;
    case SDLK_END:
        m_cursor_column = m_current.lines[m_cursor_line].length() - 3;
        m_cursor = m_current.lines[m_cursor_line].start_index + m_cursor_column;
        return true;
    case SDLK_BACKSPACE: {
        if (m_cursor > 0) {
            statement.erase(m_cursor - 1, 1);
            m_cursor--;
            m_cursor_column--;
            compile(statement);
        }
        return true;
    }
    default:
        return false;
    }
}

void Console::compile(std::string const& statement)
{
    m_current.compile(statement);
}

void Console::handle_text_input()
{
    auto str = App::instance().input_buffer();
    if (str.empty())
        return;
    std::string statement;
    if (m_current.text != nullptr)
        statement = m_current.text->str();
    if (m_cursor <= statement.length()) {
        statement.insert(m_cursor, str);
        m_cursor += str.length();
        m_cursor_column += str.length();
        compile(statement);
    }
}

void Console::mousedown(int line, int column)
{
}

void Console::motion(int line, int column)
{
}

void Console::click(int line, int column, int clicks)
{
}

void Console::wheel(int lines)
{
}

void Console::execute()
{
    m_current.execute(m_ctx);
    m_current.line = 0u;
    if (!m_statements.empty()) {
        auto& last = m_statements.back();
        m_current.line = last.line + last.lines.size();
    }
    m_statements.push_back(m_current);
    m_current = {};
    m_current.lines.emplace_back();
    m_current.lines.back().tokens.emplace_back(Span {}, Scribble::OKPrompt, "*> ");
    m_cursor_line = 0;
    m_cursor_column = 0;
    m_cursor = 0;
}

} // Scratch
