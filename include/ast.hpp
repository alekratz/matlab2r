#ifndef AST_HPP
#define AST_HPP

#include <memory>

/* Forward declaration of the visitor class */
class visitor;
typedef std::shared_ptr<visitor> visitor_p;

#include "ast/node.hpp"
#include "ast/list_node.hpp"
#include "ast/qualified_id_item.hpp"
#include "ast/qualified_id.hpp"
#include "ast/array_row_list.hpp"
#include "ast/array_col_list.hpp"
#include "ast/primary_expression.hpp"
#include "ast/postfix_expression.hpp"
#include "ast/unary_expression.hpp"
#include "ast/expression.hpp"
#include "ast/index_expression.hpp"
#include "ast/index_expression_list.hpp"

#include "ast/naked_arg_list.hpp"
#include "ast/catch_statement.hpp"
#include "ast/try_statement.hpp"
#include "ast/jump_statement.hpp"
#include "ast/iteration_statement.hpp"
#include "ast/for_statement.hpp"
#include "ast/while_statement.hpp"

/* Include visitor at the end so all classes have access to it */
#include "visitor.hpp"
#endif