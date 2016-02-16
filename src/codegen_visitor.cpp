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
    cout << " <- ";
    rhs->accept(this);
}

void codegen_visitor::visit(expression* expr)
{
    if(expr->op != expression_op::NONE)
    {
        out << '(';
        auto lhs = expr->lhs;
        auto rhs = expr->rhs;
        assert(lhs != nullptr && "left hand side of expression is null, when it should not be");
        assert(rhs != nullptr && "right hand side of expression is null, when it should not be");
        lhs->accept(this);
        switch(expr->op)
        {
        case expression_op::COLON: out << ":"; break;
        case expression_op::VBAR: out << " | "; break;
        case expression_op::AMP: out << " & "; break;
        case expression_op::EQ_OP: out << " == "; break;
        case expression_op::NE_OP: out << " != "; break;
        case expression_op::LT_OP: out << " < "; break;
        case expression_op::GT_OP: out << " > "; break;
        case expression_op::LE_OP: out << " <= "; break;
        case expression_op::GE_OP: out << " >= "; break;
        case expression_op::PLUS: out << " + "; break;
        case expression_op::MINUS: out << " - "; break;
        case expression_op::TIMES: out << " * "; break;
        case expression_op::FSLASH: out << " / "; break;
        case expression_op::BSLASH: out << " \\ "; break;
        case expression_op::POW: out << "^"; break;
        case expression_op::AMUL: out << " AMUL_OPERATOR "; break;
        case expression_op::ADIV: out << " ADIV_OPERATOR "; break;
        case expression_op::ARDIV: out << " ARDIV_OPERATOR "; break;
        case expression_op::APOW: out << " APOW_OPERATOR "; break;
        default: assert(false && "unexpected expression_op encountered");
        }
        rhs->accept(this);
        out << ')';
    }
    else
    {
        auto unary_expr = expr->expr;
        assert(unary_expr != nullptr && "unary expression portion of expession is null; this should not happen");
        unary_expr->accept(this);
    }
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
    {
        auto expr = prim_expr->expression;
        expr->accept(this);
    }
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
void codegen_visitor::visit(for_statement* for_stmt)
{
    auto range = for_stmt->range;
    auto stmt_list = for_stmt->statement_list;
    out << "for(" << for_stmt->variable << " in ";
    range->accept(this);
    out << ") {" << endl;
    indent++;
    stmt_list->accept(this);
    indent--;
    print_indent();
    out << "}";
}

void codegen_visitor::visit(while_statement* while_stmt)
{
    auto condition = while_stmt->condition;
    auto stmt_list = while_stmt->statement_list;
    out << "while(";
    condition->accept(this);
    out << ") {" << endl;
    indent++;
    stmt_list->accept(this);
    indent--;
    print_indent();
    out << "}";
}
void codegen_visitor::visit(jump_statement* jump_stmt)
{
    auto type = jump_stmt->type;
    switch(type)
    {
    case jump_statement_type::BREAK:
        out << "break";
    break;
    case jump_statement_type::CONTINUE:
        out << "next";
    break;
    case jump_statement_type::RETURN:
        /* TODO: get return statements working */
    break;
    }
}
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
void codegen_visitor::visit(if_statement* if_stmt)
{
    auto condition = if_stmt->condition;
    auto stmt_list = if_stmt->statement_list;
    auto elseifs = if_stmt->elseif_list;
    auto else_stmt = if_stmt->else_statement;
    out << "if ";
    condition->accept(this);
    out << " {" << endl;
    indent++;
    stmt_list->accept(this);
    indent--;
    print_indent();
    out << "} ";

    elseifs->children_accept(this);
    if(else_stmt != nullptr)
        else_stmt->accept(this);
}
/* void codegen_visitor::visit(elseif_list*) { } */
void codegen_visitor::visit(elseif_statement* elseif_stmt)
{
    auto condition = elseif_stmt->condition;
    auto stmt_list = elseif_stmt->statement_list;
    out << "else if ";
    condition->accept(this);
    out << " {" << endl;
    indent++;
    stmt_list->accept(this);
    indent--;
    print_indent();
    out << "} ";
}
void codegen_visitor::visit(else_statement* else_stmt)
{
    auto stmt_list = else_stmt->statement_list;
    out << "else {" << endl;
    indent++;
    stmt_list->accept(this);
    indent--;
    print_indent();
    out << "}";
}
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
