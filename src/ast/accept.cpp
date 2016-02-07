#include "ast.hpp"
#include "visitor.hpp"
#include <string>

#define VISITOR_ACCEPT_DECL(classname) void classname::accept(visitor_p guest) { guest->visit(this); }
#define TEMPLATED_ACCEPT_DECL(classname, wrapped) template<> \
    void classname::accept(visitor_p guest) { guest->visit(dynamic_cast<wrapped*>(this)); }

namespace ast
{

TEMPLATED_ACCEPT_DECL(list_node<expression>, array_row_list)
TEMPLATED_ACCEPT_DECL(list_node<array_row_list>, array_col_list)
TEMPLATED_ACCEPT_DECL(list_node<index_expression>, index_expression_list)

VISITOR_ACCEPT_DECL(qualified_id_item)
VISITOR_ACCEPT_DECL(qualified_id)
VISITOR_ACCEPT_DECL(expression)
VISITOR_ACCEPT_DECL(unary_expression)
VISITOR_ACCEPT_DECL(postfix_expression)
VISITOR_ACCEPT_DECL(primary_expression)
VISITOR_ACCEPT_DECL(index_expression)

VISITOR_ACCEPT_DECL(naked_arg_list)
VISITOR_ACCEPT_DECL(catch_statement)
VISITOR_ACCEPT_DECL(try_statement)
VISITOR_ACCEPT_DECL(for_statement)
VISITOR_ACCEPT_DECL(while_statement)
VISITOR_ACCEPT_DECL(jump_statement)
VISITOR_ACCEPT_DECL(global_statement)
VISITOR_ACCEPT_DECL(identifier_list)

} /* namespace ast */