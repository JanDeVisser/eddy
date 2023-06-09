/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Widget/Command.h>
#include <App/EditorState.h>
#include <Lexer/BasicParser.h>

using namespace Obelix;

namespace eddy::parser {

class EddyParser {
public:
    virtual ~EddyParser() = default;
    [[nodiscard]] virtual Token const& next_token() = 0;
    [[nodiscard]] virtual DisplayToken colorize(TokenCode, std::string_view const&) = 0;
    [[nodiscard]] virtual std::vector<Command> commands() const;
    [[nodiscard]] virtual std::optional<ScheduledCommand> command(std::string const&) const;
    [[nodiscard]] virtual bool parsed() const = 0;
    virtual void assign(std::string const&) = 0;
    virtual void invalidate() = 0;
    virtual ErrorOr<void,SystemError> read_file(std::string const&, BufferLocator* locator = nullptr) = 0;

protected:
    EddyParser() = default;
};

class BasicEddyParser : public BasicParser, public EddyParser {
    [[nodiscard]] bool parsed() const override { return !tokens().empty(); }
    void assign(std::string const& text) override { BasicParser::assign(text); }
    void invalidate() override { BasicParser::invalidate(); }
    ErrorOr<void,SystemError> read_file(std::string const& path, BufferLocator* locator = nullptr) override { return BasicParser::read_file(path, locator); }
protected:
    BasicEddyParser() = default;
};

} // Eddy::Parser
