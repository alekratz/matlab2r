#include "ast.hpp"

namespace ast
{

void expression_statement::children_accept(visitor_p guest)
{
	expression->accept(guest);
}

void expression_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    expression->traverse_top_down(guest);
}

void expression_statement::traverse_bottom_up(visitor_p guest)
{
	expression->traverse_bottom_up(guest);
    accept(guest);
}

}