/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <App/Scratch.h>
#include <Parser/Scribble.h>
#include <Scribble/Parser.h>
#include <Scribble/Interp/Interpreter.h>
#include <Widget/Alert.h>

namespace scratch::parser {

using namespace scratch::interp;
using namespace scratch::scribble;

ScribbleCommands::ScribbleCommands()
{
    register_command(
        { "evaluate-buffer", "Evaluates the script in the current buffer", {},
            [](Widget& w, strings const&) -> void {
                auto* doc = Scratch::editor()->document();
                auto& text = doc->text();
                auto project_maybe = compile_project(doc->path(), std::make_shared<StringBuffer>(text));
                if (project_maybe.is_error()) {
                    doc->bottom(false);
                    doc->insert("\n// " + project_maybe.error().to_string());
                    return;
                }
                auto result = interpret(std::dynamic_pointer_cast<Project>(project_maybe.value()));
                if (result.is_error()) {
                    doc->bottom(false);
                    doc->insert("\n// " + result.error().to_string());
                    return;
                }
                auto r = std::dynamic_pointer_cast<interp::ExpressionResult>(result.value());
                doc->bottom(false);
                doc->insert("\n// " + r->value().to_string());
            } },
        { SDLK_e, KMOD_CTRL });
}

ScribbleCommands ScribbleParser::s_scribble_commands;

ScribbleParser::ScribbleParser()
    : ScratchParser()
{
}

DisplayToken ScribbleParser::colorize(TokenCode code, std::string_view const& text)
{
    return token_for(code, text);
}

Token const& ScribbleParser::next_token()
{
    return m_scribble.lex();
}

std::optional<ScheduledCommand> ScribbleParser::command(std::string const& name) const
{
    if (auto* cmd = s_scribble_commands.get(name); cmd != nullptr)
        return ScheduledCommand { dynamic_cast<Widget&>(*Scratch::editor()->buffer()), *cmd };
    return {};
}

std::vector<Command> ScribbleParser::commands() const
{
    return *s_scribble_commands;
}

DisplayToken ScribbleParser::token_for(TokenCode code, std::string_view const& text)
{
    DisplayToken ret { text, PaletteIndex::Default };
    PaletteIndex color;
    if (code >= TokenCode::Keyword0 && code <= TokenCode::Keyword30) {
        color = PaletteIndex::Keyword;
    } else {
        switch (code) {
        case TokenCode::Comment:
            color = PaletteIndex::Comment;
            break;
        case TokenCode::Identifier:
            color = PaletteIndex::Identifier;
            break;
        case TokenCode::DoubleQuotedString:
        case TokenCode::UnclosedDoubleQuotedString:
            color = PaletteIndex::String;
            break;
        case TokenCode::SingleQuotedString:
        case TokenCode::UnclosedSingleQuotedString:
            color = PaletteIndex::CharLiteral;
            break;
        case Scribble::KeywordTrue:
        case Scribble::KeywordFalse:
        case TokenCode::Integer:
        case TokenCode::Float:
            color = PaletteIndex::Number;
            break;
        case Scribble::OKPrompt:
            color = PaletteIndex::ANSIBrightGreen;
            ret.text = "*> ";
            break;
        case Scribble::ErrorPrompt:
            color = PaletteIndex::ANSIBrightRed;
            ret.text = "*> ";
            break;
        case Scribble::ContinuationPrompt:
            color = PaletteIndex::Default;
            ret.text = "-> ";
            break;
        default:
            color = PaletteIndex::Punctuation;
            break;
        }
    }
    ret.color = color;
    return ret;
}

} // Scratch
