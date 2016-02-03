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

class primary_expression;
typedef std::shared_ptr<primary_expression> primary_expression_p;

class primary_expression
    : public node
{
public:
    primary_expression() = default; 
    virtual ~primary_expression() = default;
    
    qualified_id_p qualified_id;
    std::string string_lit;
    double constant;
    array_col_list_p array;
    expression_p expression;

    primary_expression_type type;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest)
    { 
        switch(type)
        {
        case primary_expression_type::QUALIFIED_ID:
            assert(qualified_id != nullptr && "primary_expression with type of QUALIFIED_ID has null or empty qualified_id container value.")
            qualified_id->accept(guest);
            break;
        case primary_expression_type::MATRIX: 
        case primary_expression_type::CELL_ARRAY:
            assert(array != nullptr && "primary_expression with type of MATRIX or CELL_ARRAY has null or empty array container value.")
            array->accept(guest);
            break;
        case primary_expression_type::EXPRESSION:
            assert(expression != nullptr && "primary_expression with type of EXPRESSION has null or empty expression container value.")
            expression->accept(guest);
            break;
        }
    }
    virtual void traverse_top_down(visitor_p guest)
    { 
        accept(guest);
        switch(type)
        {
        case primary_expression_type::QUALIFIED_ID:
            assert(qualified_id != nullptr && "primary_expression with type of QUALIFIED_ID has null or empty qualified_id container value.")
            qualified_id->traverse_top_down(guest);
            break;
        case primary_expression_type::MATRIX: 
        case primary_expression_type::CELL_ARRAY:
            assert(array != nullptr && "primary_expression with type of MATRIX or CELL_ARRAY has null or empty array container value.")
            array->traverse_top_down(guest);
            break;
        case primary_expression_type::EXPRESSION:
            assert(expression != nullptr && "primary_expression with type of EXPRESSION has null or empty expression container value.")
            expression->traverse_top_down(guest);
            break;
        }
    }
    virtual void traverse_bottom_up(visitor_p guest)
    { 
        switch(type)
        {
        case primary_expression_type::QUALIFIED_ID:
            assert(qualified_id != nullptr && "primary_expression with type of QUALIFIED_ID has null or empty qualified_id container value.")
            qualified_id->traverse_bottom_up(guest);
            break;
        case primary_expression_type::MATRIX: 
        case primary_expression_type::CELL_ARRAY:
            assert(array != nullptr && "primary_expression with type of MATRIX or CELL_ARRAY has null or empty array container value.")
            array->traverse_bottom_up(guest);
            break;
        case primary_expression_type::EXPRESSION:
            assert(expression != nullptr && "primary_expression with type of EXPRESSION has null or empty expression container value.")
            expression->traverse_bottom_up(guest);
            break;
        }
    }
};

};

#endif