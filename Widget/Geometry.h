/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <valarray>

#include <Core/Logging.h>

namespace eddy {

template <std::integral Ret=size_t, std::integral X, std::integral Y>
Ret better_max(X x, Y y)
{
    if constexpr (std::is_unsigned_v<X>) {
        if (static_cast<std::make_signed_t<X>>(x) < 0) {
            x = 0;
        }
    }
    if constexpr (std::is_unsigned_v<Y>) {
        if (static_cast<std::make_signed_t<Y>>(y) < 0) {
            y = 0;
        }
    }
    if (x < y)
        return static_cast<Ret>(y);
    return static_cast<Ret>(x);
}

template <std::integral Ret=size_t, std::integral V, std::integral Lo, std::integral Hi>
Ret clamp(V v, Lo lo, Hi hi)
{
    if constexpr (std::is_unsigned_v<Lo>) {
        auto lo_signed = static_cast<std::make_signed_t<Lo>>(lo);
        if (lo_signed < 0) {
            lo = 0;
        }
    }
    oassert(lo <= hi, "{} > {} for v = {}", lo, hi, v);
    Ret ret;
    if constexpr (std::is_signed_v<V> && std::is_unsigned_v<Ret>) {
        if (v < 0) {
            ret = static_cast<Ret>(-v);
        } else {
            ret = static_cast<Ret>(v);
        }
    } else {
        ret = static_cast<Ret>(v);
    }

    if (ret < lo)
        ret = lo;
    if (ret > hi)
        ret = hi;

    return ret;
}

template<typename T>
bool intersects(T px, T py, T x0, T y0, T x1, T y1)
{
    return (px > std::min(x0, x1) && px < std::max(x0, x1)) && (py > std::min(y0, y1) && py < std::max(y0, y1));
}

template <size_t Dim, typename ...Args>
constexpr bool CheckParameterPackSize()
{
    return sizeof...(Args) == Dim;
}


template <typename T, typename A1, typename ...Args>
constexpr bool CheckParameterType()
{
    return (std::is_convertible<A1,T>());
}

template <std::integral L, std::integral T, std::integral W, std::integral H>
SDL_Rect make_SDL_Rect(L left, T top, W width, H height)
{
    return {
        static_cast<int>(left),
        static_cast<int>(top),
        static_cast<int>(width),
        static_cast<int>(height)
    };
}


template <typename T, size_t Dim=2>
struct Vector {
    std::valarray<T> coordinates { Dim };

    Vector()
    {
        for (auto ix = 0u; ix < Dim; ++ix)
            coordinates[ix] = 0;
    }

    template <typename ...Args>
    explicit Vector(Args... values)
    requires (CheckParameterPackSize<Dim, Args...>() && CheckParameterType<T, Args...>())
        : coordinates { { std::forward<Args>(values)... } }
    {
    }

    const T& operator[](size_t idx) const
    {
        assert(idx < Dim);
        return coordinates[idx];
    }

    T& operator[](size_t idx)
    {
        assert(idx < Dim);
        return coordinates[idx];
    }

private:
};

struct Tuple {
    size_t coordinates[2] = { 0, 0 };

    template <std::unsigned_integral X, std::unsigned_integral Y>
    Tuple(X x, Y y)
    {
        coordinates[0] = x;
        coordinates[1] = y;
    }
    template <std::unsigned_integral X, std::signed_integral Y>
    Tuple(X x, Y y)
    {
        coordinates[0] = x;
        coordinates[1] = (y < 0) ? 0ul : static_cast<size_t>(y);
    }
    template <std::signed_integral X, std::unsigned_integral Y>
    Tuple(X x, Y y)
    {
        coordinates[0] = (x < 0) ? 0ul : static_cast<size_t>(x);
        coordinates[1] = y;
    }
    template <std::signed_integral X, std::signed_integral Y>
    Tuple(X x, Y y)
    {
        coordinates[0] = (x < 0) ? 0ul : static_cast<size_t>(x);
        coordinates[1] = (y < 0) ? 0ul : static_cast<size_t>(y);
    }
    Tuple() = default;

    const size_t& operator[](size_t idx) const
    {
        assert(idx < 2);
        return coordinates[idx];
    }

    size_t& operator[](size_t idx)
    {
        assert(idx < 2);
        return coordinates[idx];
    }

    [[nodiscard]] std::string to_string() const
    {
        return Obelix::format("{}x{}", coordinates[0], coordinates[1]);
    }

    [[nodiscard]] size_t x() const { return coordinates[0]; }
    [[nodiscard]] size_t y() const { return coordinates[1]; }
};

struct Position : public Tuple {
    template <std::integral L, std::integral T>
    Position(L left, T top)
        : Tuple(left, top)
    {
    }

    Position() = default;

    [[nodiscard]] size_t left() const { return coordinates[0]; }
    [[nodiscard]] size_t top() const { return coordinates[1]; }
    [[nodiscard]] size_t column() const { return coordinates[0]; }
    [[nodiscard]] size_t line() const { return coordinates[1]; }
};

struct Size : public Tuple {
    template <std::integral W, std::integral H>
    Size(W width, H height)
        : Tuple(width, height)
    {
    }
    Size() = default;

    [[nodiscard]] size_t width() const { return coordinates[0]; }
    [[nodiscard]] size_t height() const { return coordinates[1]; }
    [[nodiscard]] bool empty() const { return (coordinates[0] + coordinates[1]) == 0; }
};

struct Box {
    template <std::integral L, std::integral T, std::integral W, std::integral H>
    Box(L left, T top, W width, H height)
        : position(left, top)
        , size(width, height)
    {
    }
    Box(Position p, Size s)
        : position(p)
        , size(s)
    {
    }
    Box() = default;

    Position position;
    Size size;

    [[nodiscard]] size_t top() const { return position.top(); }
    [[nodiscard]] size_t left() const { return position.left(); }
    [[nodiscard]] size_t bottom() const { return position.top() + size.height(); }
    [[nodiscard]] size_t right() const { return position.left() + size.width(); }
    [[nodiscard]] size_t width() const { return size.width(); }
    [[nodiscard]] size_t height() const { return size.height(); }
    [[nodiscard]] size_t column() const { return left(); }
    [[nodiscard]] size_t line() const { return top(); }
    [[nodiscard]] size_t columns() const { return width(); }
    [[nodiscard]] size_t lines() const { return height(); }

    [[nodiscard]] bool empty() const { return size.empty(); }
    [[nodiscard]] bool contains(size_t x, size_t y) const
    {
        return intersects(x, y, left(), top(), right(), bottom());
    }

    [[nodiscard]] std::string to_string() const
    {
        return Obelix::format("{}+{}", position, size);
    }

    explicit operator SDL_Rect() const
    {
        return make_SDL_Rect(left(), right(), width(), height());
    }
};

struct Vec2 : public Vector<float,2> {
    Vec2(float x, float y)
        : Vector(x, y)
    {
    }
    Vec2() = default;

    [[nodiscard]] float x() const { return coordinates[0]; }
    [[nodiscard]] float y() const { return coordinates[1]; }
};

struct Rect : public Vector<float,4> {
    Rect(float x, float y, float w, float h)
        : Vector(x, y, w, h)
    {
    }

    [[nodiscard]] float x() const { return coordinates[0]; }
    [[nodiscard]] float y() const { return coordinates[1]; }
    [[nodiscard]] float width() const { return coordinates[2]; }
    [[nodiscard]] float height() const { return coordinates[3]; }
};

}
