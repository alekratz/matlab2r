#ifndef AST_HPP
#define AST_HPP

#include <memory>

#define AST_ITEM(AST) class AST; \
typedef std::shared_ptr<AST> AST ## _p;
#define AST_LIST_ITEM(WRAPPED, CLASS) typedef list_node<WRAPPED> CLASS; \
typedef std::shared_ptr<CLASS> CLASS ## _p;

namespace ast
{
AST_ITEM(node)
template<typename wrapped>
class list_node;
AST_ITEM(qualified_id_item)
AST_ITEM(qualified_id)
AST_ITEM(primary_expression)
AST_ITEM(postfix_expression)
AST_ITEM(unary_expression)
AST_ITEM(expression)
AST_ITEM(index_expression)
AST_ITEM(statement)
AST_ITEM(block_statement)
AST_ITEM(naked_arg_list)
AST_ITEM(catch_statement)
AST_ITEM(try_statement)
AST_ITEM(global_statement)
AST_ITEM(clear_statement)
AST_ITEM(identifier_list)
AST_ITEM(jump_statement)
AST_ITEM(for_statement)
AST_ITEM(while_statement)
AST_ITEM(if_statement)
AST_ITEM(elseif_statement)
AST_ITEM(else_statement)

AST_LIST_ITEM(expression, array_row_list)
AST_LIST_ITEM(array_row_list, array_col_list)
AST_LIST_ITEM(index_expression, index_expression_list)
AST_LIST_ITEM(statement, statement_list)
AST_LIST_ITEM(elseif_statement, elseif_list)
}

/* Forward declaration of the visitor class */
class visitor;
typedef std::shared_ptr<visitor> visitor_p;

#include "ast/node.hpp"
#include "ast/list_node.hpp"
#include "ast/qualified_id_item.hpp"
#include "ast/qualified_id.hpp"
#include "ast/primary_expression.hpp"
#include "ast/postfix_expression.hpp"
#include "ast/unary_expression.hpp"
#include "ast/expression.hpp"
#include "ast/index_expression.hpp"

#include "ast/statement.hpp"
#include "ast/block_statement.hpp"
#include "ast/naked_arg_list.hpp"
#include "ast/catch_statement.hpp"
#include "ast/try_statement.hpp"
#include "ast/identifier_list.hpp"
#include "ast/global_statement.hpp"
#include "ast/clear_statement.hpp"
#include "ast/jump_statement.hpp"
#include "ast/for_statement.hpp"
#include "ast/while_statement.hpp"
#include "ast/if_statement.hpp"
#include "ast/elseif_statement.hpp"
#include "ast/else_statement.hpp"

/* Include visitor at the end so all classes have access to it */
#include "visitor.hpp"
#endif