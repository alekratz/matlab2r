#include "ast.hpp"

namespace ast
{

void try_statement::children_accept(visitor_p guest)
{
    base_t::children_accept(guest);
    if(catch_statement != nullptr) catch_statement->accept(guest);
}

void try_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    base_t::traverse_top_down(guest);
    if(catch_statement != nullptr) catch_statement->traverse_top_down(guest);
}

void try_statement::traverse_bottom_up(visitor_p guest)
{
    if(catch_statement != nullptr) catch_statement->traverse_bottom_up(guest);
    base_t::traverse_bottom_up(guest);
    accept(guest);
}

}