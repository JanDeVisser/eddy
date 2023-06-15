/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Parser/EddyParser.h>

namespace eddy::parser {

std::vector<Command> EddyParser::commands() const
{
    return {};
}

std::optional<ScheduledCommand> EddyParser::command(std::string const&) const
{
    return {};
}

}
