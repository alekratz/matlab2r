#include "visitor.hpp"
#include "ast.hpp"

using namespace ast;
using namespace std;

function_name_visitor::function_name_visitor()
{

}

void function_name_visitor::visit(function_declare* fundecl)
    { function_names.insert(fundecl->name); }

void function_name_visitor::visit(ast::statement_list* stmt_list)
{
    for(auto stmt : stmt_list->items)
        stmt->traverse_top_down(this);
}