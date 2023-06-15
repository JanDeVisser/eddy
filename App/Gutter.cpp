/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Core/Format.h>

#include <App/Eddy.h>
#include <App/Gutter.h>

namespace eddy {

Gutter::Gutter()
    : WindowedWidget(SizePolicy::Characters, 10)
{
    set_renderer([](WindowedWidget* gutter) -> void {
        auto *doc = Eddy::editor()->document();
        if (doc == nullptr)
            return;
        auto screen_top = doc->screen_top();
        auto lines = doc->line_count();
        auto rows = Eddy::editor()->rows();
        for (auto row = 0; row < rows && screen_top + row < lines; ++row) {
            auto x = 24;
            auto y = Eddy::editor()->line_top(row);

            auto line = screen_top + row;
            auto color = PaletteIndex::LineNumber;
            if (line == doc->point_line())
                color = PaletteIndex::ANSIBrightYellow;
            gutter->render_fixed(x, (int)y, Obelix::format("{>4}", line + 1),
                Eddy::eddy().color(color));
        }
    });
}

}
