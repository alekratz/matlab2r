#include "ast.hpp"

namespace ast
{

void qualified_id::children_accept(visitor_p guest)
{
    for(auto item : items)
        item->accept(guest);
}
void qualified_id::traverse_top_down(visitor_p guest)
{
    accept(guest);
    for(auto item : items)
        item->traverse_top_down(guest);
}
void qualified_id::traverse_bottom_up(visitor_p guest)
{ 
    for(auto item : items)
        item->traverse_bottom_up(guest);
    accept(guest);
}

}