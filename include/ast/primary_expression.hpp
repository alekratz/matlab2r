#ifndef PRIMARY_EXPRESSION_HPP
#define PRIMARY_EXPRESSION_HPP

#include <cassert>
#include <iostream>

namespace ast
{


enum class primary_expression_type
{
    QUALIFIED_ID,
    STRING_LIT,
    CONSTANT,
    MATRIX,
    CELL_ARRAY,
    EXPRESSION,
};

enum class unary_op
{
    NONE,
    PLUS,
    MINUS,
    TILDE,
};

enum class postfix_op
{
    TRANSPOSE,
    NCTRANSPOSE,
};

class primary_expression
    : public node
{
public:
    primary_expression(qualified_id_p qualified_id)
        : qualified_id(qualified_id)
        , type(primary_expression_type::QUALIFIED_ID)
        , u_op(unary_op::NONE) { }
    primary_expression(std::string string_lit)
        : string_lit(string_lit)
        , type(primary_expression_type::STRING_LIT)
        , u_op(unary_op::NONE) { }
    primary_expression(double constant)
        : constant(constant)
        , type(primary_expression_type::CONSTANT)
        , u_op(unary_op::NONE) { }
    primary_expression(array_col_list_p array, primary_expression_type type)
        : array(array)
        , type(type)
        , u_op(unary_op::NONE) { }
    primary_expression(expression_p expression)
        : expression(expression)
        , type(primary_expression_type::EXPRESSION)
        , u_op(unary_op::NONE) { }
    virtual ~primary_expression() = default;
    
    qualified_id_p qualified_id;
    std::string string_lit;
    double constant;
    array_col_list_p array;
    expression_p expression;
    primary_expression_type type;

    /* postfix expression items */
    std::vector<postfix_op> transposes;
    /* unary expression items */
    unary_op u_op;

public:
    /* postfix expression items */
    void add_front(postfix_op op) { transposes.insert(transposes.begin(), op); }

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);

};

};

#endif