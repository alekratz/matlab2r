#include "ast.hpp"

namespace ast
{

template <typename wrapped>
void list_node<wrapped>::children_accept(visitor_p guest)
{
    for(auto item : items)
        if(item != nullptr) item->accept(guest);
}

template <typename wrapped>
void list_node<wrapped>::traverse_top_down(visitor_p guest)
{
    accept(guest);
    for(auto item : items)
        if(item != nullptr) item->traverse_top_down(guest);
}

template <typename wrapped>
void list_node<wrapped>::traverse_bottom_up(visitor_p guest)
{
    for(auto item : items)
        if(item != nullptr) item->traverse_bottom_up(guest);
    accept(guest);
}

}