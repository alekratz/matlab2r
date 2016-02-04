#include "ast.hpp"

void array_col_list::accept(visitor_p guest)
    { guest->visit(this); }
void array_col_list::children_accept(visitor_p guest)
{
    for(auto row : rows)
        row->accept(guest);
}
void array_col_list::traverse_top_down(visitor_p guest)
{
    accept(guest);
    for(auto row : rows)
        row->traverse_top_down(guest);
}
void array_col_list::traverse_bottom_up(visitor_p guest)
{
    for(auto row : rows)
        row->traverse_bottom_up(guest);
    accept(guest);
}