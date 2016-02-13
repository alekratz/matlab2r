#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cassert>

namespace ast
{

enum class expression_op
{
    COLON,
    VBAR,
    AMP,
    EQ_OP,
    NE_OP,
    LT_OP,
    GT_OP,
    LE_OP,
    GE_OP,
    PLUS,
    MINUS,
    TIMES,
    FSLASH,
    BSLASH,
    POW,
    AMUL,
    ADIV,
    ARDIV,
    APOW,
    NONE,
};


class expression
    : public node
{
public:
    expression(unary_expression_p expr) 
        : lhs(nullptr)
        , op(expression_op::NONE)
        , rhs(nullptr)
        , expr(expr) { }
    expression(expression_p lhs, expression_op op, expression_p rhs) 
        : lhs(lhs)
        , op(op)
        , rhs(rhs) 
        , expr(nullptr) { assert(op != expression_op::NONE && "operator for expression must exist with a defined left hand side"); }
    virtual ~expression() = default;
    
    expression_p lhs;
    expression_op op;
    expression_p rhs;

    unary_expression_p expr;
public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

};

#endif