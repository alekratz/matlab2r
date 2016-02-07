#include "ast.hpp"

namespace ast
{

void while_statement::children_accept(visitor_p guest)
{
    condition->accept(guest);
    statement_list->accept(guest);
}

void while_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    condition->traverse_top_down(guest);
    statement_list->traverse_top_down(guest);
}

void while_statement::traverse_bottom_up(visitor_p guest)
{
    statement_list->traverse_bottom_up(guest);
    condition->traverse_bottom_up(guest);
    accept(guest);
}

}