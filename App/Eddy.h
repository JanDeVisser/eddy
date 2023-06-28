/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <App/Editor.h>
#include <App/Gutter.h>
#include <App/StatusBar.h>
#include <Widget/App.h>

namespace eddy {

struct Config {
public:
    Config() = default;
    Config(int argc, char const** argv);

    std::string filename;

    template <typename T>
    T cmdline_flag(std::string const& flag, T const& default_value = T()) const
    {
        if (m_cmdline_flags.contains(flag)) {
            auto val = m_cmdline_flags.at(flag);
            assert(std::holds_alternative<T>(val));
            return get<T>(val);
        }
        return default_value;
    }

    bool help { false };

private:
    std::unordered_map<std::string, std::variant<std::string,bool>> m_cmdline_flags;
};

class Eddy : public App {
public:
    static void run_app(int, char const**);
    [[nodiscard]] static Editor* editor();
    [[nodiscard]] static StatusBar* status_bar();
    static void add_status_bar_applet(int, Renderer);
    static Eddy& eddy();
    Color color(PaletteIndex color);

    class EddyCommands : public Commands {
    public:
        EddyCommands();
    };

    void on_command(ScheduledCommand const&) override;

private:
    Eddy(Config& config, SDLContext *ctx);
    Config& m_config;
    Palette m_palette;

    Editor* m_editor { nullptr };
    Gutter* m_gutter { nullptr };
    StatusBar* m_status_bar { nullptr };

    static EddyCommands s_eddy_commands;
};

}
