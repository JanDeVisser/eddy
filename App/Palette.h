/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <array>

namespace scratch {

enum class PaletteIndex : uint8_t {
    Default,
    Keyword,
    Number,
    String,
    CharLiteral,
    Punctuation,
    Preprocessor,
    Identifier,
    KnownIdentifier,
    PreprocIdentifier,
    Comment,
    MultiLineComment,
    Background,
    Cursor,
    Selection,
    ErrorMarker,
    Breakpoint,
    LineNumber,
    CurrentLineFill,
    CurrentLineFillInactive,
    CurrentLineEdge,
    LineEdited,
    LineEditedSaved,
    LineEditedReverted,
    ANSIBlack,
    ANSIRed,
    ANSIGreen,
    ANSIYellow,
    ANSIBlue,
    ANSIMagenta,
    ANSICyan,
    ANSIWhite,
    ANSIBrightBlack,
    ANSIBrightRed,
    ANSIBrightGreen,
    ANSIBrightYellow,
    ANSIBrightBlue,
    ANSIBrightMagenta,
    ANSIBrightCyan,
    ANSIBrightWhite,
    Max
};

using Palette = std::array<unsigned, (size_t)PaletteIndex::Max>;

}
