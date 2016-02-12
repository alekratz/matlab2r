#include "visitor.hpp"
#include "ast.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

static string pad_commas(const vector<string>& list)
{
    string result;
    for(auto it = list.begin(); it != list.end(); it++)
    {
        result += *it;
        if(it + 1 != list.end())
            result += ", ";
    }
    return result;
}

codegen_visitor::codegen_visitor()
    : out(cout)
    , indent(0)
{ }

/* void codegen_visitor::visit(ast::qualified_id*) { } */
/* void codegen_visitor::visit(ast::qualified_id_item*) { } */
void codegen_visitor::visit(ast::assignment_expression* expr) 
{
    auto lhs = expr->lhs;
    auto rhs = expr->rhs;
    lhs->children_accept(this);
    cout << " = ";
    rhs->children_accept(this);
}

void codegen_visitor::visit(ast::expression* expr)
{
    auto lhs = expr->lhs;
    auto rhs = expr->rhs;
    out << '(';
    if(lhs != nullptr)
    {
        // visit left hand side and its operator
        lhs->accept(this);
        // find the operator
        out << " OP ";
    }

    assert(rhs != nullptr && "right hand side of expression is null, when it should not be");
    rhs->accept(this);
    out << ')';
}

/* void codegen_visitor::visit(ast::unary_expression*) { } */
/* void codegen_visitor::visit(ast::postfix_expression*) { } */
/* void codegen_visitor::visit(ast::primary_expression*) { } */
/* void codegen_visitor::visit(ast::array_col_list*) { } */
/* void codegen_visitor::visit(ast::array_row_list*) { } */
/* void codegen_visitor::visit(ast::index_expression*) { } */
/* void codegen_visitor::visit(ast::index_expression_list*) { } */

void codegen_visitor::visit(ast::function_declare* fundecl)
{
    out << make_indent() << fundecl->name << " <- function (" << pad_commas(fundecl->args) << ") {" << endl;
    indent++;
    fundecl->children_accept(this);
    indent--;
    out << make_indent() << "}" << endl;
}

/* void codegen_visitor::visit(ast::catch_statement*) { } */
/* void codegen_visitor::visit(ast::try_statement*) { } */
/* void codegen_visitor::visit(ast::for_statement*) { } */
/* void codegen_visitor::visit(ast::while_statement*) { } */
/* void codegen_visitor::visit(ast::jump_statement*) { } */
/* void codegen_visitor::visit(ast::global_statement*) { } */
/* void codegen_visitor::visit(ast::clear_statement*) { } */
void codegen_visitor::visit(ast::expression_statement* stmt) { stmt->children_accept(this); }
void codegen_visitor::visit(ast::assignment_statement* stmt) { stmt->children_accept(this); }
/* void codegen_visitor::visit(ast::naked_funcall_statement*) { } */
/* void codegen_visitor::visit(ast::identifier_list*) { } */
/* void codegen_visitor::visit(ast::if_statement*) { } */
/* void codegen_visitor::visit(ast::elseif_list*) { } */
/* void codegen_visitor::visit(ast::elseif_statement*) { } */
/* void codegen_visitor::visit(ast::else_statement*) { } */
/* void codegen_visitor::visit(ast::switch_statement*) { } */
/* void codegen_visitor::visit(ast::case_list*) { } */
/* void codegen_visitor::visit(ast::case_statement*) { } */
/* void codegen_visitor::visit(ast::otherwise_statement*) { } */
/* void codegen_visitor::visit(ast::statement_list*) { } */

string codegen_visitor::make_indent()
{
    string result;
    for(size_t i = 0; i < indent; i++)
        result += "   ";
    return result;
}