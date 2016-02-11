#include "ast.hpp"

namespace ast
{

void for_statement::children_accept(visitor_p guest)
{
    range->accept(guest);
    base_t::children_accept(guest);
}

void for_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    range->traverse_top_down(guest);
    base_t::traverse_top_down(guest);
}

void for_statement::traverse_bottom_up(visitor_p guest)
{
    base_t::traverse_bottom_up(guest);
    range->traverse_bottom_up(guest);
    accept(guest);
}

}