#ifndef AST_ASSIGNMENT_EXPRESSION_HPP
#define AST_ASSIGNMENT_EXPRESSION_HPP

#include <memory>

namespace ast
{


class assignment_expression
    : node
{
public:
    typedef node base_t;

public:
    assignment_expression(postfix_expression_p lhs, expression_p rhs)
        : lhs(lhs)
        , rhs(rhs) { }

    postfix_expression_p lhs;
    expression_p rhs;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

}

#endif /* AST_ASSIGNMENT_EXPRESSION_HPP */