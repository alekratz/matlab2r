#include "ast.hpp"
#include "visitor.hpp"

#define VISITOR_ACCEPT_DECL(classname) void classname::accept(visitor_p guest) { guest->visit(this); }

namespace ast
{

VISITOR_ACCEPT_DECL(unary_op)

} /* namespace ast */