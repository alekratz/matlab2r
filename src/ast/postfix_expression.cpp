#include "ast.hpp"

namespace ast
{

void postfix_expression::children_accept(visitor_p guest)
{ 
    assert(expr != nullptr && "right hand side of postfix_expression is null, when it should not be.");
    expr->accept(guest);
}
void postfix_expression::traverse_top_down(visitor_p guest)
{ 
    accept(guest);
    assert(expr != nullptr && "right hand side of postfix_expression is null, when it should not be.");
    expr->traverse_top_down(guest);
}
void postfix_expression::traverse_bottom_up(visitor_p guest)
{ 
    accept(guest);
    assert(expr != nullptr && "right hand side of postfix_expression is null, when it should not be.");
    expr->traverse_bottom_up(guest);
}

}