/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Parser/ScratchParser.h>

namespace scratch::parser {

std::vector<Command> ScratchParser::commands() const
{
    return {};
}

std::optional<ScheduledCommand> ScratchParser::command(std::string const&) const
{
    return {};
}

}
