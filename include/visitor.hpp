#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "ast.hpp"
#include <memory>

class visitor
{
public:
    virtual ~visitor() = default;

public:
    virtual void visit(ast::qualified_id*) { }
    virtual void visit(ast::qualified_id_item*) { }
    virtual void visit(ast::expression*) { }
    virtual void visit(ast::unary_expression*) { }
    virtual void visit(ast::postfix_expression*) { }
    virtual void visit(ast::primary_expression*) { }
    virtual void visit(ast::array_col_list*) { }
    virtual void visit(ast::array_row_list*) { }
    virtual void visit(ast::index_expression*) { }
    virtual void visit(ast::index_expression_list*) { }
    virtual void visit(ast::naked_arg_list*) { }
    virtual void visit(ast::catch_statement*) { }
    virtual void visit(ast::try_statement*) { }
};

typedef std::shared_ptr<visitor> visitor_p;

#endif