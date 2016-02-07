#include "ast.hpp"

namespace ast
{

void catch_statement::children_accept(visitor_p guest)
{
    statement_list->accept(guest);
}

void catch_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    statement_list->traverse_top_down(guest);
}

void catch_statement::traverse_bottom_up(visitor_p guest)
{
    statement_list->traverse_bottom_up(guest);
    accept(guest);
}

}