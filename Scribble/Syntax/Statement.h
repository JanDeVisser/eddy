/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Scribble/Syntax/Syntax.h>
#include <Scribble/Syntax/Expression.h>

namespace eddy::scribble {

ABSTRACT_NODE_CLASS(Statement, SyntaxNode)
public:
    Statement() = default;
    explicit Statement(Span);
};

using pStatement = std::shared_ptr<Statement>;
using Statements = std::vector<pStatement>;

NODE_CLASS(Import, Statement)
public:
    Import(Span, std::string);
    [[nodiscard]] std::string attributes() const override;
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] std::string const& name() const;
    [[nodiscard]] bool is_complete() const override { return !m_name.empty(); }

private:
    std::string m_name;
};

NODE_CLASS(Pass, Statement)
public:
    explicit Pass(Span);
    explicit Pass(std::shared_ptr<Statement> elided_statement);
    [[nodiscard]] std::shared_ptr<Statement> const& elided_statement() const;
    [[nodiscard]] std::string text_contents() const override;
    [[nodiscard]] std::string to_string() const override;

private:
    std::shared_ptr<Statement> m_elided_statement;
};

class Goto;

NODE_CLASS(Label, Statement)
public:
    explicit Label(Span = {});
    explicit Label(std::shared_ptr<Goto> const&);
    [[nodiscard]] std::string attributes() const override;
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] int label_id() const;
    [[nodiscard]] bool is_complete() const override { return m_label_id > 0; }
    static int reserve_id();

private:
    static int m_current_id;
    int m_label_id;
};

NODE_CLASS(Goto, Statement)
public:
    explicit Goto(Span = {}, std::shared_ptr<Label> const& = nullptr);
    [[nodiscard]] std::string attributes() const override;
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] int label_id() const;
    [[nodiscard]] bool is_complete() const override { return m_label_id > 0; }

private:
    int m_label_id;
};

NODE_CLASS(Block, Statement)
public:
    explicit Block(Span, Statements);
    [[nodiscard]] Statements const& statements() const;
    [[nodiscard]] Nodes children() const override;
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] bool is_complete() const override;

protected:
    Statements m_statements {};
};

NODE_CLASS(Module, Block)
public:
    Module(Statements const&, std::string, std::shared_ptr<StringBuffer>, std::vector<Token> = {});
    Module(Span, Statements const&, std::string, std::shared_ptr<StringBuffer>, std::vector<Token> = {});
    Module(std::shared_ptr<Module> const&, Statements const&, std::vector<Token> = {});
    [[nodiscard]] std::string attributes() const override;
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] std::string const& name() const;
    [[nodiscard]] std::vector<Token> const& tokens() const;
    [[nodiscard]] std::shared_ptr<StringBuffer> const& buffer() const;

private:
    std::string m_name;
    std::shared_ptr<StringBuffer> m_buffer;
    std::vector<Token> m_tokens;
};

using pModule = std::shared_ptr<Module>;
using Modules = std::vector<pModule>;

NODE_CLASS(Project, SyntaxNode)
public:
    Project(Modules, std::string, std::shared_ptr<StringBuffer>);
    Project(std::string, std::shared_ptr<StringBuffer>);
    [[nodiscard]] std::shared_ptr<StringBuffer> const& main_buffer() const;
    [[nodiscard]] Modules const& modules() const;
    [[nodiscard]] std::shared_ptr<Module> const& root() const;
    [[nodiscard]] std::string const& main_module() const;
    [[nodiscard]] Nodes children() const override;
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] std::string attributes() const override;
    [[nodiscard]] std::string root_to_xml() const;
    [[nodiscard]] int unbound_statements() const;
    [[nodiscard]] bool is_complete() const override;

private:
    Modules m_modules;
    std::shared_ptr<Module> m_root;
    std::string m_main_module;
    std::shared_ptr<StringBuffer> m_main_buffer;
};

NODE_CLASS(ExpressionStatement, Statement)
public:
    explicit ExpressionStatement(std::shared_ptr<Expression> expression);
    [[nodiscard]] std::shared_ptr<Expression> const& expression() const;
    [[nodiscard]] Nodes children() const override;
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] bool is_complete() const override;

private:
    std::shared_ptr<Expression> m_expression;
};

NODE_CLASS(Return, Statement)
public:
    Return(Span, std::shared_ptr<Expression>, bool = false);
    [[nodiscard]] Nodes children() const override;
    [[nodiscard]] std::string attributes() const override;
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] std::shared_ptr<Expression> const& expression() const;
    [[nodiscard]] bool return_error() const;
    [[nodiscard]] bool is_complete() const override;

private:
    std::shared_ptr<Expression> m_expression;
    bool m_return_error;
};

}
