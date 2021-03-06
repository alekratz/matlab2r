#include "ast.hpp"

namespace ast
{

void case_statement::children_accept(visitor_p guest)
{
	condition->accept(guest);
    base_t::children_accept(guest);
}

void case_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    condition->traverse_top_down(guest);
    base_t::traverse_top_down(guest);
}

void case_statement::traverse_bottom_up(visitor_p guest)
{
    base_t::traverse_bottom_up(guest);
	condition->traverse_bottom_up(guest);
    accept(guest);
}

}