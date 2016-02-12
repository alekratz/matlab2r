#include "ast.hpp"

namespace ast
{

void array_index::children_accept(visitor_p guest)
{
    index_expression_list->accept(guest);
}

void array_index::traverse_top_down(visitor_p guest)
{
    accept(guest);
    index_expression_list->traverse_top_down(guest);
}

void array_index::traverse_bottom_up(visitor_p guest)
{
    index_expression_list->traverse_bottom_up(guest);
    accept(guest);
}

}