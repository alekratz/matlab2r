#ifndef UNARY_EXPRESSION_HPP
#define UNARY_EXPRESSION_HPP

#include <cassert>
#include <iostream>

namespace ast
{


enum class unary_op
{
    NONE,
    PLUS,
    MINUS,
    TILDE,
};

class unary_expression
    : public node
{
public:
    unary_expression(postfix_expression_p expr) 
        : op(unary_op::NONE)
        , expr(expr) { }
    unary_expression(unary_op op, postfix_expression_p expr) 
        : op(op)
        , expr(expr) { }
    virtual ~unary_expression() = default;
    
    unary_op op;
    postfix_expression_p expr;
public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

};

#endif