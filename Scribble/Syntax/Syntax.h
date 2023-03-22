/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdarg>
#include <memory>
#include <string>
#include <vector>

#include <core/Logging.h>
#include <lexer/Token.h>

#include <Scribble/Syntax/SyntaxNodeType.h>

namespace scratch::scribble {

using namespace Obelix;

extern_logging_category(scribble);

#define ABSTRACT_NODE_CLASS(name, derives_from) \
    class name;                                 \
    using p##name = std::shared_ptr<name>;      \
    using name##s = std::vector<p##name>;       \
    class name                                  \
        : public derives_from {

#define NODE_CLASS(name, derives_from, ...)                     \
    class name;                                                 \
    using p##name = std::shared_ptr<name>;                      \
    using name##s = std::vector<p##name>;                       \
    class name                                                  \
        : public derives_from                                   \
          __VA_OPT__(, ) __VA_ARGS__ {                          \
    public:                                                     \
        [[nodiscard]] SyntaxNodeType node_type() const override \
        {                                                       \
            return SyntaxNodeType::name;                        \
        }                                                       \
                                                                \
    private:

#define NODE_CLASS_TEMPLATE(name, derives_from, ...)            \
    class name                                                  \
        : public derives_from                                   \
          __VA_OPT__(, ) __VA_ARGS__ {                          \
    public:                                                     \
        [[nodiscard]] SyntaxNodeType node_type() const override \
        {                                                       \
            return SyntaxNodeType::name;                        \
        }                                                       \
                                                                \
    private:

class SyntaxNode;
using Nodes = std::vector<std::shared_ptr<SyntaxNode>>;
using Strings = std::vector<std::string>;

class SyntaxNode : public std::enable_shared_from_this<SyntaxNode> {
public:
    explicit SyntaxNode(Span location = {});
    virtual ~SyntaxNode() = default;

    [[nodiscard]] virtual SyntaxNodeType node_type() const = 0;
    [[nodiscard]] virtual std::string text_contents() const;
    [[nodiscard]] virtual std::string attributes() const;
    [[nodiscard]] virtual Nodes children() const;
    [[nodiscard]] std::string to_xml(int) const;
    [[nodiscard]] virtual std::string to_string() const;
    [[nodiscard]] std::string to_xml() const;
    [[nodiscard]] Span const& location() const;
    [[nodiscard]] virtual bool is_complete() const { return false; }

private:
    Span m_location;
};

using pSyntaxNode = std::shared_ptr<SyntaxNode>;
using SyntaxNodes = Nodes;

template<class NodeClass>
NODE_CLASS_TEMPLATE(NodeList, SyntaxNode, public std::vector<std::shared_ptr<NodeClass>>)
public :

    explicit NodeList(std::string tag)
    : SyntaxNode()
    , m_tag(std::move(tag))
{
}

NodeList(std::string tag, std::vector<std::shared_ptr<NodeClass>> nodes)
    : SyntaxNode()
    , std::vector<std::shared_ptr<NodeClass>>(std::move(nodes))
    , m_tag(std::move(tag))
{
}

[[nodiscard]] std::string const& tag() const { return m_tag; }

[[nodiscard]] std::string attributes() const override
{
    return format(R"(tag="{}")", tag());
}

[[nodiscard]] Nodes children() const override
{
    Nodes ret;
    for (auto const& element : *this) {
        ret.push_back(element);
    }
    return ret;
}

private:
std::string m_tag;
};

template<class T, class... Args>
std::shared_ptr<T> make_node(Args&&... args)
{
    auto ret = std::make_shared<T>(std::forward<Args>(args)...);
    debug(scribble, "{}: {}", SyntaxNodeType_name(ret->node_type()), ret->to_string());
    return ret;
}

template <class ...Args>
inline Span merge(pSyntaxNode const& node_1, pSyntaxNode const& node_2, Args&&... args)
{
    if (node_1 != nullptr) {
        return merge(node_1, std::forward<Args>(args)...);
    } else if (node_2 != nullptr){
        return merge(node_2, std::forward<Args>(args)...);
    } else {
        return merge(std::forward<Args>(args)...);
    }
}

template <class ...Args>
inline Span merge(pSyntaxNode const& node_1, Token const& token_2, Args&&... args)
{
    if (node_1 != nullptr) {
        return merge(node_1, std::forward<Args>(args)...);
    } else {
        return merge(token_2, std::forward<Args>(args)...);
    }
}

template <class ...Args>
inline Span merge(Token const& token_1, pSyntaxNode const&, Args&&... args)
{
    return merge(token_1, std::forward<Args>(args)...);
}

template <class ...Args>
inline Span merge(Token const& token_1, Token const&, Args&&... args)
{
    return merge(token_1, std::forward<Args>(args)...);
}

inline Span merge(pSyntaxNode const& node_1, Token const& token_2)
{
    if (node_1 != nullptr)
        return node_1->location().merge(token_2.location());
    else
        return token_2.location();
}

inline Span merge(pSyntaxNode const& node_1, pSyntaxNode const& node_2)
{
    if (node_1 != nullptr) {
        if (node_2 != nullptr) {
            return node_1->location().merge(node_2->location());
        } else {
            return node_1->location();
        }
    } else {
        if (node_2 != nullptr) {
            return node_2->location();
        } else {
            fatal("Need at least one non-null syntaxnode to merge locations");
        }
    }
}

inline Span merge(Token const& token_1, Token const& token_2)
{
    return token_1.location().merge(token_2.location());
}

inline Span merge(Token const& token_1, pSyntaxNode const& node_2)
{
    if (node_2 != nullptr)
        return token_1.location().merge(node_2->location());
    else
        return token_1.location();
}

}
