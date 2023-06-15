/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>

#include <SDL.h>

namespace eddy {

struct SDLKey {
    SDL_Keycode sym { SDLK_UNKNOWN };
    uint16_t mod { KMOD_NONE };

    SDLKey() = default;
    SDLKey(SDL_Keycode, uint32_t);
    SDLKey(SDL_Keysym const&);

    int operator<=>(SDLKey const& other) const;
    [[nodiscard]] std::string to_string() const;
};

} // Eddy
