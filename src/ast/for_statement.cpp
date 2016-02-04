#include "ast.hpp"

namespace ast
{

void for_statement::children_accept(visitor_p guest)
{
    range->accept(guest);
    // statement_list->accept(guest);
}

void for_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    range->traverse_top_down(guest);
    // statement_list->traverse_top_down(guest);
}

void for_statement::traverse_bottom_up(visitor_p guest)
{
    // statement_list->traverse_bottom_up(guest);
    range->traverse_bottom_up(guest);
    accept(guest);
}

}