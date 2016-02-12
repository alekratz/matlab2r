#include "visitor.hpp"
#include "ast.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;
using namespace ast;

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

void codegen_visitor::visit(qualified_id* q_id)
{
    auto items = q_id->items;
    for(auto it = items.begin(); it != items.end(); it++)
    {
        (*it)->accept(this);
        if(it + 1 != items.end())
            out << "$";
    }
}

void codegen_visitor::visit(qualified_id_item* q_id_item)
{
    switch(q_id_item->type)
    {
    case qualified_id_item_type::EXPRESSION:
        q_id_item->expression->accept(this);
    break;
    case qualified_id_item_type::IDENTIFIER:
        out << q_id_item->identifier;
    break;
    }

    if(q_id_item->array_index_list != nullptr)
    {
        /* TODO */
        q_id_item->array_index_list->children_accept(this);
    }
}

void codegen_visitor::visit(assignment_expression* expr) 
{
    auto lhs = expr->lhs;
    auto rhs = expr->rhs;
    lhs->accept(this);
    cout << " = ";
    rhs->accept(this);
}

void codegen_visitor::visit(expression* expr)
{
    auto lhs = expr->lhs;
    auto rhs = expr->rhs;
    out << '(';
    if(lhs != nullptr)
    {
        // visit left hand side and its operator
        lhs->accept(this);
        // TODO : find the operator
        out << " OP ";
    }

    assert(rhs != nullptr && "right hand side of expression is null, when it should not be");
    rhs->accept(this);
    out << ')';
}

void codegen_visitor::visit(unary_expression* unexpr)
{
    switch(unexpr->op)
    {
    case unary_op::PLUS: out << "+";
    case unary_op::MINUS: out << "-";
    case unary_op::TILDE: out << "~";
    case unary_op::NONE: break;
    default: assert(false && "unknown unary_op type encountered");
    }

    auto expr = unexpr->expr;
    assert(expr != nullptr && "unary_expression's wrapped expression should not be null");
    expr->accept(this);
}
void codegen_visitor::visit(postfix_expression* post_expr)
{
    auto expr = post_expr->expr;
    expr->accept(this);

    for(auto tp : post_expr->transposes)
    {
        switch(tp)
        {
        case postfix_op::TRANSPOSE: /* TODO */ break;
        case postfix_op::NCTRANSPOSE: /* TODO */ break;
        }
    }
}
void codegen_visitor::visit(primary_expression* prim_expr)
{
    switch(prim_expr->type)
    {
    case primary_expression_type::QUALIFIED_ID:
    {
        auto q_id = prim_expr->qualified_id;
        q_id->children_accept(this);
    }
    break;
    case primary_expression_type::STRING_LIT:
        out << prim_expr->string_lit;
    break;
    case primary_expression_type::CONSTANT:
        out << prim_expr->constant;
    break;
    case primary_expression_type::MATRIX:
        /* TODO */
        out << "MATRIX";
    break;
    case primary_expression_type::CELL_ARRAY:
        /* TODO */
        out << "CELL_ARRAY";
    break;
    case primary_expression_type::EXPRESSION:
        /* TODO */
        out << "EXPRESSION";
    break;
    default:
        assert(false && "unknown primary_expression_type encountered");
        break;
    }
}

/* void codegen_visitor::visit(array_col_list*) { } */
/* void codegen_visitor::visit(array_row_list*) { } */
/* void codegen_visitor::visit(index_expression*) { } */
/* void codegen_visitor::visit(index_expression_list*) { } */

void codegen_visitor::visit(function_declare* fundecl)
{
    out << fundecl->name << " <- function (" << pad_commas(fundecl->args) << ") {" << endl;
    indent++;
    fundecl->statement_list->accept(this);
    indent--;
    out << "}" << endl;
}

/* void codegen_visitor::visit(catch_statement*) { } */
/* void codegen_visitor::visit(try_statement*) { } */
/* void codegen_visitor::visit(for_statement*) { } */
/* void codegen_visitor::visit(while_statement*) { } */
/* void codegen_visitor::visit(jump_statement*) { } */
/* void codegen_visitor::visit(global_statement*) { } */
/* void codegen_visitor::visit(clear_statement*) { } */
void codegen_visitor::visit(expression_statement* stmt) { stmt->children_accept(this); }
void codegen_visitor::visit(assignment_statement* stmt) { stmt->children_accept(this); }
void codegen_visitor::visit(naked_funcall_statement* stmt)
{
    out << stmt->identifier;
    out << "(";
    out << pad_commas(stmt->args);
    out << ")";
}
/* void codegen_visitor::visit(identifier_list*) { } */
/* void codegen_visitor::visit(if_statement*) { } */
/* void codegen_visitor::visit(elseif_list*) { } */
/* void codegen_visitor::visit(elseif_statement*) { } */
/* void codegen_visitor::visit(else_statement*) { } */
/* void codegen_visitor::visit(switch_statement*) { } */
/* void codegen_visitor::visit(case_list*) { } */
/* void codegen_visitor::visit(case_statement*) { } */
/* void codegen_visitor::visit(otherwise_statement*) { } */

void codegen_visitor::visit(statement* stmt) { out << "STATEMENT"; }

void codegen_visitor::visit(statement_list* stmt_list)
{
    for(auto stmt : stmt_list->items)
    {
        print_indent();
        stmt->accept(this);
        out << endl;
    }
}
