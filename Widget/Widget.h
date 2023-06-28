/*
 * Copyright (c) 2022, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <functional>

#include <App/Forward.h>
#include <Widget/Command.h>
#include <Widget/Geometry.h>
#include <Widget/GraphicsContext.h>

namespace eddy {

enum class TextAlignment {
    Left,
    Right,
    Center,
};

class Widget : public std::enable_shared_from_this<Widget> {
public:
    virtual ~Widget() = default;

    virtual void render();
    virtual bool dispatch(SDL_Keysym);
    virtual void handle_mousedown(SDL_MouseButtonEvent const&) { }
    virtual void handle_click(SDL_MouseButtonEvent const&) { }
    virtual void handle_wheel(SDL_MouseWheelEvent const&) { }
    virtual void handle_motion(SDL_MouseMotionEvent const&) { }
    virtual void handle_text_input() { }
    virtual void resize(Box const&);
    [[nodiscard]] virtual std::optional<ScheduledCommand> command(std::string const&) const;
    [[nodiscard]] virtual std::vector<ScheduledCommand> commands() const;

protected:
    Widget() = default;
    Commands* m_commands { nullptr };
};

enum class SizePolicy {
    Absolute = 0,
    Relative,
    Characters,
    Calculated,
    Stretch,
};

class WindowedWidget;
class WidgetContainer;

using Renderer = std::function<void(WindowedWidget*)>;
using KeyHandler = std::function<bool(WindowedWidget*, SDL_Keysym)>;
using MouseButtonHandler = std::function<void(WindowedWidget*, SDL_MouseButtonEvent const&)>;
using MouseWheelHandler = std::function<void(WindowedWidget*, SDL_MouseWheelEvent const&)>;
using MouseMotionHandler = std::function<void(WindowedWidget*, SDL_MouseMotionEvent const&)>;
using TextHandler = std::function<void(WindowedWidget*)>;
using SizeCalculator = std::function<int(WindowedWidget*)>;

class WindowedWidget : public Widget {
public:
    WindowedWidget(SizePolicy = SizePolicy::Stretch, size_t = 0);
    WindowedWidget(SizeCalculator);

    [[nodiscard]] virtual size_t height() const;
    [[nodiscard]] virtual size_t width() const;
    [[nodiscard]] virtual size_t top() const;
    [[nodiscard]] virtual size_t left() const;
    [[nodiscard]] Position offset() const { return { left(), top() }; }
    [[nodiscard]] bool empty() const;
    [[nodiscard]] SizePolicy policy() const;
    [[nodiscard]] size_t policy_size() const;
    [[nodiscard]] WidgetContainer const* parent() const;

    [[nodiscard]] Position position() const;
    [[nodiscard]] Size size() const;
    [[nodiscard]] Box const& outline() const;
    void set_renderer(Renderer);
    void set_keyhandler(KeyHandler);
    void set_mousedownhandler(MouseButtonHandler);
    void set_mouseclickhandler(MouseButtonHandler);
    void set_mousewheelhandler(MouseWheelHandler);
    void set_mousemotionhandler(MouseMotionHandler);
    void set_texthandler(TextHandler);
    void set_size_calculator(SizeCalculator);
    void render() override;
    bool dispatch(SDL_Keysym) override;
    void handle_mousedown(SDL_MouseButtonEvent const&) override;
    void handle_click(SDL_MouseButtonEvent const&) override;
    void handle_wheel(SDL_MouseWheelEvent const&) override;
    void handle_motion(SDL_MouseMotionEvent const&) override;
    void handle_text_input() override;
    void resize(Box const&) override;
    size_t calculate_size();

    template <std::integral X, std::integral Y, class Str>
    Box render_text(X x, Y y, Str text,
        Color const& color = Color { 255, 255, 255, 255 },
        TextAlignment alignment = TextAlignment::Left,
        GraphicsContext::FontFamily family = GraphicsContext::FontFamily::Fixed) const
    {
        return _render_text(
            clamp(x, 0, width()),
            clamp(y, 0, height()),
            std::string(text),
            color,
            alignment,
            family
        );
    }

    template <std::integral X, std::integral Y, class Str>
    Box render_fixed(X x, Y y, Str text, Color const& color = Color { 255, 255, 255, 255 }) const
    {
        return _render_text(
            clamp(x, 0, width()),
            clamp(y, 0, height()),
            std::string(text),
            color,
            TextAlignment::Left,
            GraphicsContext::FontFamily::Fixed
        );
    }

    template <std::integral X, std::integral Y, class Str>
    Box render_fixed_right_aligned(X x, Y y, Str text, Color const& color = Color { 255, 255, 255, 255 }) const
    {
        return _render_text(
            clamp(x, 0, width()),
            clamp(y, 0, height()),
            std::string(text),
            color,
            TextAlignment::Right,
            GraphicsContext::FontFamily::Fixed
        );
    }

    template <std::integral Y, class Str>
    Box render_fixed_centered(Y y, Str text, Color const& color = Color { 255, 255, 255, 255 }) const
    {
        return _render_text(
            0,
            clamp(y, 0, height()),
            std::string(text),
            color,
            TextAlignment::Center,
            GraphicsContext::FontFamily::Fixed
        );
    }

    template <std::floating_point Y, class Str>
    Box render_fixed_centered(Y y, Str text, Color const& color = Color { 255, 255, 255, 255 }) const
    {
        return _render_text(
            0,
            clamp<int>(static_cast<size_t>(y), 0ul, height()),
            std::string(text),
            color,
            TextAlignment::Center,
            GraphicsContext::FontFamily::Fixed
        );
    }

    template <std::integral L, std::integral T, std::integral W, std::integral H>
    Box normalize(L l, T t, W w, H h) const
    {
        if constexpr (std::is_signed_v<L>) {
            if (l < 0)
                l = width() + l;
        }
        if constexpr (std::is_signed_v<T>) {
            if (t < 0)
                t = height() + t;
        }
        if constexpr (std::is_signed_v<W>) {
            if (w <= 0)
                w = width() + w;
        }
        if constexpr (std::is_signed_v<H>) {
            if (h <= 0)
                h = height() + h;
        }
        l = clamp(l, 0, width());
        t = clamp(t, 0, height());
        return Box(l, t, clamp(w, 0, width() - l), clamp(h, 0, height() - t));
    }

    template <std::integral L, std::integral T, std::integral W, std::integral H>
    void box(L l, T t, W w, H h, Color color) const
    {
        _box(normalize(l, t, w, h), color);
    }

    template <std::integral L, std::integral T, std::integral W, std::integral H>
    void rectangle(L l, T t, W w, H h, Color color) const
    {
        _rectangle(normalize(l, t, w, h), color);
    }

    template <std::integral L, std::integral T, std::integral W, std::integral H, std::integral R>
    void roundedRectangle(L l, T t, W w, H h, R radius, Color color) const
    {
        _roundedRectangle(normalize(l, t, w, h), static_cast<int>(radius), color);
    }

protected:
private:
    friend class WidgetContainer;
    void set_parent(WidgetContainer *parent) { m_parent = parent; }
    Box _render_text(size_t x, size_t y, std::string const& text,
        Color const& color = Color { 255, 255, 255, 255 },
        TextAlignment = TextAlignment::Left,
        GraphicsContext::FontFamily = GraphicsContext::FontFamily::Fixed) const;
    void _box(Box const& rect, Color color) const;
    void _roundedBox(Box const& rect, int radius, Color color) const;
    void _rectangle(Box const& rect, Color color) const;
    void _roundedRectangle(Box const& rect, int radius, Color color) const;

    SizePolicy m_policy { SizePolicy::Absolute };
    size_t m_size { 0 };
    Box m_outline;
    WidgetContainer* m_parent { nullptr };

    Renderer m_renderer { nullptr };
    KeyHandler m_keyhandler { nullptr };
    MouseButtonHandler m_mousedownhandler { nullptr };
    MouseButtonHandler m_mouseclickhandler { nullptr };
    MouseWheelHandler m_mousewheelhandler { nullptr };
    MouseMotionHandler m_mousemotionhandler { nullptr };
    TextHandler m_texthandler { nullptr };
    SizeCalculator m_size_calculator { nullptr };
};

enum class ContainerOrientation {
    Vertical = 0,
    Horizontal,
};

class WidgetContainer {
public:
    explicit WidgetContainer(ContainerOrientation);
    void add_component(WindowedWidget*);
    void remove_component(WindowedWidget*);
    [[nodiscard]] std::vector<Widget*> components() const;
    void resize(Box const&);

    template <class ComponentClass>
    requires std::derived_from<ComponentClass, WindowedWidget>
    ComponentClass* get_component()
    {
        for (auto& c : components()) {
            if (auto casted = dynamic_cast<ComponentClass*>(c); casted != nullptr)
                return casted;
        }
        return nullptr;
    }

    void handle_mousedown(Box const&, SDL_MouseButtonEvent const&);
    void handle_click(Box const&, SDL_MouseButtonEvent const&);
    void handle_wheel(Box const&, SDL_MouseWheelEvent const&);
    void handle_motion(Box const&, SDL_MouseMotionEvent const&);

private:
    ContainerOrientation m_orientation { ContainerOrientation::Vertical };
    std::vector<std::unique_ptr<WindowedWidget>> m_components;
    std::vector<Box> m_outlines;
    Widget* m_mouse_focus { nullptr };
};

class Layout : public WindowedWidget {
public:
    Layout(ContainerOrientation, SizePolicy = SizePolicy::Stretch, int = 0);
    void render() override;
    bool dispatch(SDL_Keysym) override;
    void resize(Box const&) override;
    std::vector<Widget*> components();
    void add_component(WindowedWidget*);
    void remove_component(WindowedWidget*);
    WidgetContainer const& container() const;
    void handle_mousedown(SDL_MouseButtonEvent const&) override;
    void handle_click(SDL_MouseButtonEvent const&) override;
    void handle_wheel(SDL_MouseWheelEvent const&) override;
    void handle_motion(SDL_MouseMotionEvent const&) override;
    std::optional<ScheduledCommand> command(std::string const&) const override;
    [[nodiscard]] std::vector<ScheduledCommand> commands() const override;

    template <class ComponentClass>
    requires std::derived_from<ComponentClass, WindowedWidget>
    ComponentClass* get_component()
    {
        return m_container.get_component<ComponentClass>();
    }

protected:
    WidgetContainer& container();

private:
    WidgetContainer m_container;
};

enum class FrameStyle {
    None,
    Rectangle,
    Rounded,
};

class Frame : public WindowedWidget {
public:
    Frame(FrameStyle, size_t, WindowedWidget*, SizePolicy = SizePolicy::Stretch, size_t = 0);
    void render() override;
    bool dispatch(SDL_Keysym) override;
    void resize(Box const&) override;
    [[nodiscard]] WindowedWidget* contents();
    [[nodiscard]] size_t margin() const;
    [[nodiscard]] size_t clamped_margin() const;
    [[nodiscard]] FrameStyle frame_style() const;

private:
    FrameStyle m_frame_style { FrameStyle::None };
    size_t m_margin { 3 };
    size_t m_clamped_margin { 3 };
    std::unique_ptr<WindowedWidget> m_contents;
};

class ModalWidget : public WindowedWidget {
public:
    ModalWidget(int, int);
    void dismiss();

    [[nodiscard]] size_t width() const override;
    [[nodiscard]] size_t height() const override;
    [[nodiscard]] size_t top() const override;
    [[nodiscard]] size_t left() const override;

private:
    int m_width;
    int m_height;
};

}
