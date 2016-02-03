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

};

typedef std::shared_ptr<visitor> visitor_p;

#endif