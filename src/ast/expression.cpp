#include "ast.hpp"

namespace ast
{

void expression::children_accept(visitor_p guest)
{ 
    if(lhs != nullptr) lhs->accept(guest);
    assert(rhs != nullptr && "right hand side of expression is null, when it should not be.");
    rhs->accept(guest);
}

void expression::traverse_top_down(visitor_p guest)
{ 
    accept(guest);
    if(lhs != nullptr) lhs->traverse_top_down(guest);
    assert(rhs != nullptr && "right hand side of expression is null, when it should not be.");
    rhs->traverse_top_down(guest);
}

void expression::traverse_bottom_up(visitor_p guest)
{ 
    accept(guest);
    if(lhs != nullptr) lhs->traverse_bottom_up(guest);
    assert(rhs != nullptr && "right hand side of expression is null, when it should not be");
    rhs->traverse_bottom_up(guest);
}
}