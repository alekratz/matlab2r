#include "ast.hpp"

namespace ast
{

void expression::children_accept(visitor_p guest)
{ 
    if(op == expression_op::NONE) {
        assert(expr != nullptr && "expr is null, when it should not be");
        expr->accept(guest);
    }
    else {
        assert(lhs != nullptr && "left hand side of expression is null, when it should not be");
        lhs->accept(guest);
        assert(rhs != nullptr && "right hand side of expression is null, when it should not be");
        rhs->accept(guest);
    }
}

void expression::traverse_top_down(visitor_p guest)
{ 
    accept(guest);
    if(op == expression_op::NONE) {
        assert(expr != nullptr && "expr is null, when it should not be");
        expr->traverse_top_down(guest);
    }
    else {
        assert(lhs != nullptr && "left hand side of expression is null, when it should not be");
        lhs->traverse_top_down(guest);
        assert(rhs != nullptr && "right hand side of expression is null, when it should not be");
        rhs->traverse_top_down(guest);
    }
}

void expression::traverse_bottom_up(visitor_p guest)
{ 
    if(op == expression_op::NONE) {
        assert(expr != nullptr && "expr is null, when it should not be");
        expr->traverse_bottom_up(guest);
    }
    else {
        assert(lhs != nullptr && "left hand side of expression is null, when it should not be");
        lhs->traverse_bottom_up(guest);
        assert(rhs != nullptr && "right hand side of expression is null, when it should not be");
        rhs->traverse_bottom_up(guest);
    }
    accept(guest);
}
}