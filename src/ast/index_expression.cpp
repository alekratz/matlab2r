#include "ast.hpp"

namespace ast
{

void index_expression::children_accept(visitor_p guest)
    { if(!is_colon_op) expr->accept(guest); }

void index_expression::traverse_top_down(visitor_p guest)
{
    accept(guest);
    if(!is_colon_op) expr->traverse_top_down(guest);    
}

void index_expression::traverse_bottom_up(visitor_p guest)
{
    if(!is_colon_op) expr->traverse_bottom_up(guest);    
    accept(guest);
}

}