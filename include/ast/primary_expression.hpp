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

class expression;
typedef std::shared_ptr<expression> expression_p;
class qualified_id;
typedef std::shared_ptr<qualified_id> qualified_id_p;

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
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

};

#endif