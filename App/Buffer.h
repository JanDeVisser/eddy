/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <numeric>

#include <App/EditorState.h>
#include <Lexer/Token.h>
#include <Widget/Widget.h>

using namespace Obelix;

namespace eddy {

class Buffer : public Widget {
public:
    [[nodiscard]] int rows() const;
    [[nodiscard]] int columns() const;
    [[nodiscard]] virtual std::string title() const = 0;
    [[nodiscard]] virtual std::string short_title() const;
    [[nodiscard]] virtual std::string status() const = 0;
    virtual void on_activate() {};
    virtual void on_deactivate() {};
    virtual void mousedown(Position) {};
    virtual void motion(Position) {};
    virtual void click(Position, int) {};
    virtual void wheel(int) {};

protected:
    explicit Buffer(Editor*);
    [[nodiscard]] Editor* editor() { return m_editor; }

private:
    Editor* m_editor;
};

} // Eddy
