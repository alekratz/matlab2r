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

class expression;
typedef std::shared_ptr<expression> expression_p;

class expression
    : public node
{
public:
    expression(unary_expression_p rhs) 
        : lhs(nullptr)
        , op(expression_op::NONE)
        , rhs(rhs) { }
    expression(expression_p lhs, expression_op op, unary_expression_p rhs) 
        : lhs(lhs)
        , op(op)
        , rhs(rhs) { assert(op != expression_op::NONE && "operator for expression must exist with a defined left hand side"); }
    virtual ~expression() = default;
    
    expression_p lhs;
    expression_op op;
    unary_expression_p rhs;
public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest)
    { 
        if(lhs != nullptr) lhs->accept(guest);
        assert(rhs != nullptr && "right hand side of expression is null, when it should not be.");
        rhs->accept(guest);
    }
    virtual void traverse_top_down(visitor_p guest)
    { 
        accept(guest);
        if(lhs != nullptr) lhs->traverse_top_down(guest);
        assert(rhs != nullptr && "right hand side of expression is null, when it should not be.");
        rhs->traverse_top_down(guest);
    }
    virtual void traverse_bottom_up(visitor_p guest)
    { 
        accept(guest);
        if(lhs != nullptr) lhs->traverse_bottom_up(guest);
        assert(rhs != nullptr && "right hand side of expression is null, when it should not be");
        rhs->traverse_bottom_up(guest);
    }
};

};

#endif