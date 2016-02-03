#include "ast.hpp"
#include "visitor.hpp"

#define VISITOR_ACCEPT_DECL(classname) void classname::accept(visitor_p guest) { guest->visit(this); }

namespace ast
{

VISITOR_ACCEPT_DECL(qualified_id_item)
VISITOR_ACCEPT_DECL(qualified_id)
VISITOR_ACCEPT_DECL(expression)
VISITOR_ACCEPT_DECL(unary_expression)
VISITOR_ACCEPT_DECL(postfix_expression)
VISITOR_ACCEPT_DECL(primary_expression)

} /* namespace ast */