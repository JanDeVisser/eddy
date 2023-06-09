/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Scribble/Syntax/Syntax.h>

namespace eddy::scribble {

extern_logging_category(scribble);

// -- SyntaxNode ------------------------------------------------------------

SyntaxNode::SyntaxNode(Span location)
    : m_location(std::move(location))
{
}

std::string SyntaxNode::text_contents() const
{
    return "";
}

std::string SyntaxNode::attributes() const
{
    return "";
}

Nodes SyntaxNode::children() const
{
    return Nodes {};
}

std::string SyntaxNode::to_xml(int indent) const
{
    std::string ret = "";
    while (static_cast<int>(ret.length()) < indent)
        ret += ' ';
    ret += format("<{}", node_type());
    auto attrs = attributes();
    auto child_nodes = children();
    auto text = text_contents();
    if (!attrs.empty()) {
        ret += " " + attrs;
    }
    if (text.empty() && child_nodes.empty())
        return ret + "/>";
    ret += ">\n";
    for (auto& child : child_nodes) {
        ret += child->to_xml(indent + 2);
        ret += "\n";
    }
    ret += text;
    for (auto ix = 0; ix < indent; ix++)
        ret += ' ';
    return ret + format("</{}>", node_type());
}

std::string SyntaxNode::to_string() const
{
    return SyntaxNodeType_name(node_type());
}

std::string SyntaxNode::to_xml() const
{
    return to_xml(0);
}

Span const& SyntaxNode::location() const
{
    return m_location;
}

}
