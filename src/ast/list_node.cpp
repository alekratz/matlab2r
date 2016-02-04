#include "ast.hpp"
#include <string>

namespace ast
{

#define DECLARE_SPECIALIZATION(wrapped) template<> \
void list_node<wrapped>::children_accept(visitor_p guest) \
{ \
    for(auto item : items) \
        if(item != nullptr) item->accept(guest); \
} \
template<> \
void list_node<wrapped>::traverse_top_down(visitor_p guest) \
{ \
    accept(guest); \
    for(auto item : items) \
        if(item != nullptr) item->traverse_top_down(guest); \
} \
template<> \
void list_node<wrapped>::traverse_bottom_up(visitor_p guest) \
{ \
    for(auto item : items) \
        if(item != nullptr) item->traverse_bottom_up(guest); \
    accept(guest); \
}

DECLARE_SPECIALIZATION(expression)          // array_row_list
DECLARE_SPECIALIZATION(array_row_list)      // array_col_list
DECLARE_SPECIALIZATION(index_expression)    // index_expression_list

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