#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <memory>

#define AST_ITEM(AST) class AST; \
typedef std::shared_ptr<AST> AST ## _p;
#define AST_LIST_ITEM(WRAPPED, CLASS) typedef list_node<WRAPPED> CLASS; \
typedef std::shared_ptr<CLASS> CLASS ## _p;

namespace ast
{
AST_ITEM(node);
template<typename wrapped>
class list_node;
AST_ITEM(qualified_id_item);
AST_ITEM(qualified_id);
AST_ITEM(array_index);
AST_ITEM(primary_expression);
AST_ITEM(postfix_expression);
AST_ITEM(unary_expression);
AST_ITEM(expression);
AST_ITEM(index_expression);
AST_ITEM(assignment_expression);
AST_ITEM(statement);
AST_ITEM(block_statement);
AST_ITEM(naked_funcall_statement);
AST_ITEM(catch_statement);
AST_ITEM(try_statement);
AST_ITEM(global_statement);
AST_ITEM(clear_statement);
AST_ITEM(identifier_list);
AST_ITEM(expression_statement);
AST_ITEM(assignment_statement);
AST_ITEM(jump_statement);
AST_ITEM(for_statement);
AST_ITEM(while_statement);
AST_ITEM(if_statement);
AST_ITEM(elseif_statement);
AST_ITEM(else_statement);
AST_ITEM(switch_statement);
AST_ITEM(case_statement);
AST_ITEM(otherwise_statement);
AST_ITEM(function_declare);

AST_LIST_ITEM(expression, array_row_list);
AST_LIST_ITEM(array_row_list, array_col_list);
AST_LIST_ITEM(index_expression, index_expression_list);
AST_LIST_ITEM(statement, statement_list);
AST_LIST_ITEM(elseif_statement, elseif_list);
AST_LIST_ITEM(case_statement, case_list);
AST_LIST_ITEM(array_index, array_index_list);

enum class eostmt_type : uint32_t
{
    NEWLINE,
    COMMA,
    SEMICOLON,
};

}

/* Forward declaration of the visitor class */
class visitor;
typedef visitor* visitor_p;

#include "ast/node.hpp"
#include "ast/list_node.hpp"
#include "ast/qualified_id_item.hpp"
#include "ast/qualified_id.hpp"
#include "ast/array_index.hpp"
#include "ast/primary_expression.hpp"
#include "ast/postfix_expression.hpp"
#include "ast/unary_expression.hpp"
#include "ast/assignment_expression.hpp"
#include "ast/expression.hpp"
#include "ast/index_expression.hpp"

#include "ast/statement.hpp"
#include "ast/block_statement.hpp"
#include "ast/catch_statement.hpp"
#include "ast/try_statement.hpp"
#include "ast/identifier_list.hpp"
#include "ast/global_statement.hpp"
#include "ast/clear_statement.hpp"
#include "ast/expression_statement.hpp"
#include "ast/assignment_statement.hpp"
#include "ast/jump_statement.hpp"
#include "ast/for_statement.hpp"
#include "ast/while_statement.hpp"
#include "ast/if_statement.hpp"
#include "ast/elseif_statement.hpp"
#include "ast/else_statement.hpp"
#include "ast/switch_statement.hpp"
#include "ast/case_statement.hpp"
#include "ast/otherwise_statement.hpp"
#include "ast/naked_funcall_statement.hpp"
#include "ast/function_declare.hpp"

#endif