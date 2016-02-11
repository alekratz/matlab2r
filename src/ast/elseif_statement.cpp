#include "ast.hpp"

namespace ast
{

void elseif_statement::children_accept(visitor_p guest)
{
    condition->accept(guest);
    base_t::children_accept(guest);
}

void elseif_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    condition->traverse_top_down(guest);
    base_t::traverse_top_down(guest);
}

void elseif_statement::traverse_bottom_up(visitor_p guest)
{
    base_t::traverse_bottom_up(guest);
    condition->traverse_bottom_up(guest);
    accept(guest);
}

}