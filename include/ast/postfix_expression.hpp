#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIX_EXPRESSION_HPP

#include <cassert>
#include <iostream>

namespace ast
{


enum class postfix_op
{
    TRANSPOSE,
    NCTRANSPOSE,
};

class postfix_expression
    : public node
{
public:
    postfix_expression(primary_expression_p expr) 
        : expr(expr) { }
    virtual ~postfix_expression() = default;
    
    primary_expression_p expr;
    std::vector<postfix_op> transposes;

    void add_front(postfix_op op) { transposes.insert(transposes.begin(), op); }

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

};

#endif