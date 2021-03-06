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



class primary_expression
    : public node
{
public:
    primary_expression(qualified_id_p qualified_id) : qualified_id(qualified_id), type(primary_expression_type::QUALIFIED_ID) { }
    primary_expression(std::string string_lit) : string_lit(string_lit), type(primary_expression_type::STRING_LIT) { }
    primary_expression(double constant) : constant(constant), type(primary_expression_type::CONSTANT) { }
    primary_expression(array_col_list_p array, primary_expression_type type) : array(array), type(type) { }
    primary_expression(expression_p expression) : expression(expression), type(primary_expression_type::EXPRESSION) { }
    virtual ~primary_expression() = default;
    
    qualified_id_p qualified_id;
    std::string string_lit;
    double constant;
    array_col_list_p array;
    expression_p expression;

    primary_expression_type type;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

};

#endif