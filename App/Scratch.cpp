/*
 * Copyright (c) 2022, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>

#include <core/Logging.h>

#include <App/CommandHandler.h>
#include <App/Console.h>
#include <App/Scratch.h>
#include <Widget/SDLContext.h>

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1024
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 768
#endif

namespace scratch {

using namespace Obelix;

logging_category(scratch);

Scratch::ScratchCommands::ScratchCommands()
{
    register_command({ "enlarge-font", "Enlarge editor font", {},
        [](Widget&, strings const&) -> void {
            App::instance().enlarge_font();
        }
    }, { SDLK_EQUALS, KMOD_GUI } );

    register_command({ "invoke", "Invoke command",
        {
            { "Command", CommandParameterType::Command }
        },
        [](Widget& app, strings const& args) -> void {
             if (auto scheduled_command = app.command(args[0]); scheduled_command.has_value()) {
                 App::instance().schedule(scheduled_command.value());
             }
        }
    }, { SDLK_x, KMOD_GUI });

    register_command({ "reset-font", "Reset editor font", {},
        [](Widget&, strings const&) -> void {
            auto& app = App::instance();
            app.reset_font();
        }
    }, { SDLK_0, KMOD_GUI });

    register_command({ "scratch-quit", "Quits the editor", {},
        [](Widget&, strings const&) -> void {
            App::instance().quit();
        }
    }, { SDLK_q, KMOD_CTRL });

    register_command({ "set-fixed-width-font", "Set fixed width (editor) font",
        {
            {
                "Font file name", CommandParameterType::ExistingFilename
            }
        },
        [](Widget&, strings const& args) -> void {
            Scratch::instance().set_font(args[0]);
        }
    });

    register_command({ "shrink-font", "Shrink editor font", {},
        [](Widget&, strings const&) -> void {
            App::instance().shrink_font();
        }
    }, { SDLK_MINUS, KMOD_GUI });

}

Scratch::ScratchCommands Scratch::s_scratch_commands;

Config::Config(int argc, char const** argv)
{
    for (int ix = 1; ix < argc; ++ix) {
        if ((strlen(argv[ix]) > 2) && !strncmp(argv[ix], "--", 2)) {
            if (auto eq_ptr = strchr(argv[ix], '='); eq_ptr == nullptr) {
                m_cmdline_flags[std::string(argv[ix] + 2)] = true;
            } else {
                auto ptr = argv[ix];
                ptr += 2;
                std::string flag = argv[ix] + 2;
                m_cmdline_flags[flag.substr(0, eq_ptr - ptr)] = std::string(eq_ptr + 1);
            }
            continue;
        }
        filename = argv[ix];
    }
    bool enable_log = cmdline_flag<bool>("debug", false);
    auto logfile = cmdline_flag<std::string>("log");
    if (!logfile.empty()) {
        Obelix::Logger::get_logger().set_file(logfile);
        enable_log = true;
    }
    if (enable_log)
        Obelix::Logger::get_logger().enable("scratch");
}

Scratch::Scratch(Config& config, SDLContext *ctx)
    : App("Scratch", ctx)
    , m_config(config)
    , m_palette(DarkPalette())
{
    auto icon_surface = IMG_LoadTyped_RW(SDL_RWFromFile("scratch.png", "rb"), 1, "PN");
    if(!icon_surface) {
        log_error("Could not load application icon");
        return;
    }
    SDL_SetWindowIcon(context()->window(), icon_surface);
    SDL_FreeSurface(icon_surface);
    m_commands = &s_scratch_commands;
}

Editor* Scratch::editor()
{
    return scratch().m_editor;
}

StatusBar* Scratch::status_bar()
{
    return scratch().m_status_bar;
}

void Scratch::add_status_bar_applet(int size, Renderer renderer)
{
    status_bar()->add_applet(size, std::move(renderer));
}

Scratch& Scratch::scratch()
{
    return dynamic_cast<Scratch&>(App::instance());
}

/*
 * Equivalent to:
 *    uint8_t a = (c >> 24) & 0xff;
 *    uint8_t b = (c >> 16) & 0xff;
 *    uint8_t g = (c >> 8) & 0xff;
 *    uint8_t r = c & 0xff;
 *    return { r, g, b, a };
 */
SDL_Color Scratch::color(PaletteIndex color)
{
    static unsigned s_ansicolors[] = {
        0xff000000, // ANSIBlack,
        0xff0000cc, // ANSIRed,
        0xff069a4e, // ANSIGreen,
        0xff00a0c4, // ANSIYellow,
        0xffcf9f72, // ANSIBlue,
        0xff7b5075, // ANSIMagenta,
        0xff9a9806, // ANSICyan,
        0xffcfd7d3, // ANSIWhite,
        0xff535755, // ANSIBrightBlack,
        0xff2929ef, // ANSIBrightRed,
        0xff34e28a, // ANSIBrightGreen,
        0xff4fe9fc, // ANSIBrightYellow,
        0xffffaf32, // ANSIBrightBlue,
        0xffa87fad, // ANSIBrightMagenta,
        0xffe2e234, // ANSIBrightCyan,
        0xffffffff, // ANSIBrightWhite,
    };
    uint32_t c;
    if (color >= PaletteIndex::ANSIBlack && color <= PaletteIndex::ANSIBrightWhite)
        c = s_ansicolors[(size_t)color - (size_t)PaletteIndex::ANSIBlack];
    else
        c = m_palette[(size_t)color];
    return *((SDL_Color*)&c);
}

void Scratch::on_command(ScheduledCommand const& cmd)
{
    add_modal(new CommandHandler(cmd));
}

void Scratch::run_app(int argc, char const** argv)
{
    Config config(argc, argv);
    debug(scratch, "The logger works!");

    auto ctx = new SDLContext(WINDOW_WIDTH, WINDOW_HEIGHT);
    Scratch app(config, ctx);
    auto main_area = new Layout(ContainerOrientation::Horizontal);
    app.add_component(main_area);
    app.add_component(app.m_status_bar = new StatusBar());
    app.add_status_bar_applet(7, [](WindowedWidget* applet) -> void {
        applet->render_fixed(5, 2, App::instance().last_key().to_string(), SDL_Color { 0xff, 0xff, 0xff, 0xff });
    });
    app.add_status_bar_applet(5, [](WindowedWidget* applet) -> void {
        PaletteIndex box_color;
        auto f = App::instance().fps();
        if (f >= 55) {
            box_color = PaletteIndex::ANSIGreen;
        } else if (f >= 40) {
            box_color = PaletteIndex::ANSIYellow;
        } else {
            box_color = PaletteIndex::ANSIBrightRed;
        }
        applet->box(SDL_Rect { 0, 0, 0, 0 }, Scratch::scratch().color(box_color));
        applet->render_fixed_centered(2, "fps", SDL_Color { 0xff, 0xff, 0xff, 0xff });
    });
    main_area->add_component(app.m_gutter = new Gutter());
    main_area->add_component(app.m_editor = new Editor());
//    app.m_editor->add_buffer<Console>();
    app.m_editor->add_buffer<Document>();
    if (!app.m_config.filename.empty())
        app.m_editor->open_file(app.m_config.filename);
    app.focus(app.m_editor);
    app.event_loop();
}

}
