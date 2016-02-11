#include "ast.hpp"

namespace ast
{

void switch_statement::children_accept(visitor_p guest)
{
    expression->accept(guest);
	case_list->accept(guest);
    if(otherwise_statement != nullptr) otherwise_statement->accept(guest);
}

void switch_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    expression->traverse_top_down(guest);
	case_list->traverse_top_down(guest);
    if(otherwise_statement != nullptr) otherwise_statement->traverse_top_down(guest);
}

void switch_statement::traverse_bottom_up(visitor_p guest)
{
	if(otherwise_statement != nullptr) otherwise_statement->traverse_bottom_up(guest);
	case_list->traverse_bottom_up(guest);
    expression->traverse_bottom_up(guest);
    accept(guest);
}

}