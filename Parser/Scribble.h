/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <deque>

#include <Parser/ScratchParser.h>
#include <Scribble/Scribble.h>

namespace scratch::parser {

using namespace Obelix;
using namespace scratch::scribble;

struct ScribbleCommands : public Commands {
    ScribbleCommands();
};

class ScribbleParser : public ScratchParser {
public:
    explicit ScribbleParser();
    Token const& next_token() override;
    DisplayToken colorize(TokenCode, std::string_view const&) override;
    std::optional<ScheduledCommand> command(std::string const&) const override;
    [[nodiscard]] std::vector<Command> commands() const override;
    [[nodiscard]] bool parsed() const override { return !m_scribble.tokens().empty(); }
    void assign(std::string const& text) override { m_scribble.assign(text); }
    void invalidate() override { m_scribble.invalidate(); }
    ErrorOr<void,SystemError> read_file(std::string const& path, BufferLocator* locator = nullptr) override { return m_scribble.read_file(path, locator); }

    static DisplayToken token_for(TokenCode, std::string_view const&);
private:
    Scribble m_scribble { false };
    static ScribbleCommands s_scribble_commands;
};

}
