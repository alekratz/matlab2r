#include "ast.hpp"

namespace ast
{

void otherwise_statement::children_accept(visitor_p guest)
{
    base_t::children_accept(guest);
}

void otherwise_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    base_t::traverse_top_down(guest);
}

void otherwise_statement::traverse_bottom_up(visitor_p guest)
{
    base_t::traverse_bottom_up(guest);
    accept(guest);
}

}