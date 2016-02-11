#include "ast.hpp"

namespace ast
{

void assignment_expression::children_accept(visitor_p guest)
{
    lhs->accept(guest);
    rhs->accept(guest);
}

void assignment_expression::traverse_top_down(visitor_p guest)
{
    accept(guest);
    lhs->traverse_top_down(guest);
    rhs->traverse_top_down(guest);
}

void assignment_expression::traverse_bottom_up(visitor_p guest)
{
    rhs->traverse_bottom_up(guest);
    lhs->traverse_bottom_up(guest);
    accept(guest);
}

}