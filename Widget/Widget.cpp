/*
 * Copyright (c) 2022, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Widget/App.h>
#include <Widget/SDLContext.h>
#include <Widget/Widget.h>

namespace eddy {

void Widget::render()
{
}

void Widget::resize(Box const&)
{
}

bool Widget::dispatch(SDL_Keysym sym)
{
    if (m_commands != nullptr) {
        if (auto* cmd = m_commands->command_for_key(sym); cmd != nullptr) {
            App::instance().schedule({ const_cast<Widget&>(*this), *cmd });
            return true;
        }
    }
    return false;
}

std::optional<ScheduledCommand> Widget::command(std::string const& name) const
{
    if (m_commands != nullptr) {
        if (auto* cmd = m_commands->get(name); cmd != nullptr)
            return ScheduledCommand { const_cast<Widget&>(*this), *cmd };
    }
    return {};
}

std::vector<ScheduledCommand> Widget::commands() const
{
    std::vector<ScheduledCommand> ret;
    if (m_commands != nullptr) {
        for (auto const& [ _, cmd ] : m_commands->commands()) {
            ret.push_back({ const_cast<Widget&>(*this), cmd });
        }
    }
    return ret;
}

}
