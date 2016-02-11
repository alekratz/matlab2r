#include "ast.hpp"

namespace ast
{

void if_statement::children_accept(visitor_p guest)
{
    condition->accept(guest);
    base_t::children_accept(guest);
    if(elseif_list != nullptr) elseif_list->accept(guest);
    if(else_statement != nullptr) else_statement->accept(guest);
}

void if_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    condition->traverse_top_down(guest);
    base_t::traverse_top_down(guest);
    if(elseif_list != nullptr) elseif_list->traverse_top_down(guest);
    if(else_statement != nullptr) else_statement->traverse_top_down(guest);
}

void if_statement::traverse_bottom_up(visitor_p guest)
{
    if(else_statement != nullptr) else_statement->traverse_bottom_up(guest);
    if(elseif_list != nullptr) elseif_list->traverse_bottom_up(guest);
    base_t::traverse_bottom_up(guest);
    condition->traverse_bottom_up(guest);
    accept(guest);
}

}