#ifndef AST_INDEX_EXPRESSION_HPP
#define AST_INDEX_EXPRESSION_HPP

#include <memory>

namespace ast
{

class index_expression;
typedef std::shared_ptr<index_expression> index_expression_p;

class index_expression
    : node
{
public:
    index_expression() 
        : is_colon_op(true)
        , expr(nullptr) { }

    index_expression(expression_p expr) 
        : is_colon_op(false)
        , expr(expr) { }

    bool is_colon_op;
    expression_p expr;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

}

#endif