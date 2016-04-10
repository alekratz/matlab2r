#ifndef AST_INDEX_EXPRESSION_HPP
#define AST_INDEX_EXPRESSION_HPP

#include <memory>

namespace ast
{


class index_expression
    : node
{
public:
    index_expression(bool is_colon_op=true) 
        : is_colon_op(is_colon_op)
        , expr(nullptr) 
        , named_expr(nullptr) { }

    index_expression(expression_p expr) 
        : is_colon_op(false)
        , expr(expr)
        , named_expr(nullptr) { }

    index_expression(generator::funcall_arg_assign_p named_expr) 
        : is_colon_op(false)
        , expr(nullptr)
        , named_expr(named_expr) { }

    bool is_colon_op;
    expression_p expr;
    generator::funcall_arg_assign_p named_expr;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

}

#endif