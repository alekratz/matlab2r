#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "ast.hpp"
#include <memory>

class visitor
{
public:
    virtual ~visitor() = default;

public:
    virtual void visit(ast::unary_op*) { }
    virtual void visit(ast::qualified_id*) { }
    virtual void visit(ast::qualified_id_item*) { }

};

typedef std::shared_ptr<visitor> visitor_p;

#endif