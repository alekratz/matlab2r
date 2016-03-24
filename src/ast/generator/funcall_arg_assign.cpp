#include "ast.hpp"

namespace ast
{
namespace generator
{

void funcall_arg_assign::children_accept(visitor_p guest)
{
    rhs->accept(guest);
}

void funcall_arg_assign::traverse_top_down(visitor_p guest)
{
    accept(guest);
    rhs->traverse_bottom_up(guest);
}

void funcall_arg_assign::traverse_bottom_up(visitor_p guest)
{
    rhs->traverse_bottom_up(guest);
    accept(guest);
}

} /* namespace generator */
} /* namespace generator */