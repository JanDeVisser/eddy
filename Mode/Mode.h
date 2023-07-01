/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <filesystem>
#include <functional>
#include <string_view>

#include <Core/Error.h>

#include <App/Document.h>
#include <Widget/Command.h>

namespace eddy {

namespace fs=std::filesystem;
using namespace Obelix;

PaletteIndex plain_color_for(TokenCode code);

class Mode {
public:
    explicit Mode(Document& doc);
    virtual ~Mode() = default;
    [[nodiscard]] Document const& document() const;

    using Open = std::function<ErrorOr<std::string, SystemError>(fs::path const&)>;
    using OnLoad = std::function<void(void)>;
    using OnChange = std::function<void(EditAction const&)>;
    using OnClose = std::function<void(void)>;
    using ColorFor = std::function<PaletteIndex(TokenCode)>;
    using Parse = std::function<void(Text&)>;
    using GetCommands = std::function<std::vector<Command>()>;
    using GetCommand = std::function<std::optional<ScheduledCommand>(std::string const&)>;

    Open open_file { nullptr };
    OnLoad on_load { [](){} };
    OnChange on_change { [](EditAction const&) {} };
    OnClose on_close { [](){} };
    Parse parse { nullptr };
    GetCommands commands = []() -> std::vector<Command> { return {}; };
    GetCommand command = [](std::string const&) -> std::optional<ScheduledCommand> { return {}; };
    ColorFor color_for = { nullptr };

protected:
    [[nodiscard]] Document& document();

private:
    Document& m_doc;
};

}
