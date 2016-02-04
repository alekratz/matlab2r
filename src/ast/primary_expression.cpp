#include "ast.hpp"

namespace ast
{

void primary_expression::children_accept(visitor_p guest)
{ 
    switch(type)
    {
    case primary_expression_type::QUALIFIED_ID:
        assert(qualified_id != nullptr && "primary_expression with type of QUALIFIED_ID has null or empty qualified_id container value.");
        qualified_id->accept(guest);
        break;
    case primary_expression_type::MATRIX: 
    case primary_expression_type::CELL_ARRAY:
        assert(array != nullptr && "primary_expression with type of MATRIX or CELL_ARRAY has null or empty array container value.");
        array->accept(guest);
        break;
    case primary_expression_type::EXPRESSION:
        assert(expression != nullptr && "primary_expression with type of EXPRESSION has null or empty expression container value.");
        expression->accept(guest);
        break;
    default:
        // TODO : set up logging system
        break;
    }
}
void primary_expression::traverse_top_down(visitor_p guest)
{ 
    accept(guest);
    switch(type)
    {
    case primary_expression_type::QUALIFIED_ID:
        assert(qualified_id != nullptr && "primary_expression with type of QUALIFIED_ID has null or empty qualified_id container value.");
        qualified_id->traverse_top_down(guest);
        break;
    case primary_expression_type::MATRIX: 
    case primary_expression_type::CELL_ARRAY:
        assert(array != nullptr && "primary_expression with type of MATRIX or CELL_ARRAY has null or empty array container value.");
        array->traverse_top_down(guest);
        break;
    case primary_expression_type::EXPRESSION:
        assert(expression != nullptr && "primary_expression with type of EXPRESSION has null or empty expression container value.");
        expression->traverse_top_down(guest);
        break;
    default:
        // TODO : set up logging system
        break;
    }
}
void primary_expression::traverse_bottom_up(visitor_p guest)
{ 
    switch(type)
    {
    case primary_expression_type::QUALIFIED_ID:
        assert(qualified_id != nullptr && "primary_expression with type of QUALIFIED_ID has null or empty qualified_id container value.");
        qualified_id->traverse_bottom_up(guest);
        break;
    case primary_expression_type::MATRIX: 
    case primary_expression_type::CELL_ARRAY:
        assert(array != nullptr && "primary_expression with type of MATRIX or CELL_ARRAY has null or empty array container value.");
        array->traverse_bottom_up(guest);
        break;
    case primary_expression_type::EXPRESSION:
        assert(expression != nullptr && "primary_expression with type of EXPRESSION has null or empty expression container value.");
        expression->traverse_bottom_up(guest);
        break;
    default:
        // TODO : set up logging system
        break;
    }
}

}