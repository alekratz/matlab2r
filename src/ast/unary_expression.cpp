#include "ast.hpp"

namespace ast
{

void unary_expression::children_accept(visitor_p guest)
{ 
    assert(expr != nullptr && "right hand side of unary_expression is null, when it should not be.");
    expr->accept(guest);
}
void unary_expression::traverse_top_down(visitor_p guest)
{ 
    accept(guest);
    assert(expr != nullptr && "right hand side of unary_expression is null, when it should not be.");
    expr->traverse_top_down(guest);
}
void unary_expression::traverse_bottom_up(visitor_p guest)
{ 
    accept(guest);
    assert(expr != nullptr && "right hand side of unary_expression is null, when it should not be.");
    expr->traverse_bottom_up(guest);
}

}