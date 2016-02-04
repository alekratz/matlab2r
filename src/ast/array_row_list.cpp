#include "ast.hpp"

namespace ast
{

void array_row_list::children_accept(visitor_p guest)
{
    for(auto item : items)
        item->accept(guest);
}
void array_row_list::traverse_top_down(visitor_p guest)
{
    accept(guest);
    for(auto item : items)
        item->traverse_top_down(guest);
}
void array_row_list::traverse_bottom_up(visitor_p guest)
{
    for(auto item : items)
        item->traverse_bottom_up(guest);
    accept(guest);
}

}