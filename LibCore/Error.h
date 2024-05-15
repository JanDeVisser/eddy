/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cerrno>
#include <concepts>
#include <format>
#include <optional>
#include <string>
#include <vector>

#include <LibCore/StringUtil.h>

namespace LibCore {

struct LibCError {
    static constexpr int ECUSTOM = EQFULL + 1;

    int         err_no = { 0 };
    std::string_view code = { "Unknown" };
    std::string description = { "Unknown error" };

    explicit LibCError(int err) noexcept;
    LibCError() noexcept
        : LibCError(errno)
    {
    }

    explicit LibCError(std::string const& description) noexcept
        : LibCError(ECUSTOM)
    {
        this->description = description;
    }

    template<typename... Args>
    explicit LibCError(std::string const &fmt, Args const &...args) noexcept
        : LibCError(ECUSTOM)
    {
        description = std::vformat(fmt, std::make_format_args(args...));
    }

    [[nodiscard]] std::string to_string() const
    {
        return std::format("{} ({}): {}", code, err_no, description);
    }
};

}
