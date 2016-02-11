#include "ast.hpp"

namespace ast
{

void assignment_statement::children_accept(visitor_p guest)
{
	expression->accept(guest);
}

void assignment_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    expression->traverse_top_down(guest);
}

void assignment_statement::traverse_bottom_up(visitor_p guest)
{
	expression->traverse_bottom_up(guest);
    accept(guest);
}

}