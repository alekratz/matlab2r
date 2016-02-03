#include "ast.hpp"
#include "visitor.hpp"

#define VISITOR_ACCEPT_DECL(classname) void classname::accept(visitor_p guest) { guest->visit(this); }

namespace ast
{

VISITOR_ACCEPT_DECL(unary_op)
VISITOR_ACCEPT_DECL(qualified_id_item)
VISITOR_ACCEPT_DECL(qualified_id)

} /* namespace ast */