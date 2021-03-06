#include "visitor.hpp"
#include "ast.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;
using namespace ast;

template<typename map_from, typename map_to>
struct map_function
    { virtual map_to operator()(const map_from&) = 0; };

template<typename same>
struct map_identity : map_function<same, same>
    { virtual same operator()(const same& in) { return in; } };

struct map_wrap_quotes : map_identity<string>
    { virtual string operator()(const string& in) { return "'" + in + "'"; } };

template<typename map_function_t=map_identity<string>>
static string pad_commas(const vector<string>& list)
{
    string result;
    auto map = map_function_t();
    for(auto it = list.begin(); it != list.end(); it++)
    {
        result += map(*it);
        if(it + 1 != list.end())
            result += ", ";
    }
    return result;
}

codegen_visitor::codegen_visitor(unordered_set<string> function_names)
    : out(cout)
    , indent(0)
    , function_names(function_names)
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
    auto ary_idx_list = q_id_item->array_index_list;

    switch(q_id_item->type)
    {
    case qualified_id_item_type::EXPRESSION:
        q_id_item->expression->accept(this);
    break;
    case qualified_id_item_type::IDENTIFIER:
        out << q_id_item->identifier;
        //          this gets whether we're making a function call or accessing an array
        bool funcall = (function_names.find(q_id_item->identifier) != function_names.end());
        if(ary_idx_list != nullptr)
        {
            for(auto ary_idx : ary_idx_list->items)
            {
                assert(ary_idx != nullptr && "array indexer (or funcall) is null when it should not be");
                // Only mess with unresolved types
                if(ary_idx->type == array_index_type::ARRAY_OR_FUNCALL)
                    ary_idx->type = funcall ? array_index_type::FUNCALL : array_index_type::ARRAY;
            }
        }
    break;
    }

    if(ary_idx_list != nullptr)
        ary_idx_list->accept(this);
}

void codegen_visitor::visit(array_index_list* ary_idx_list)
{
    for(auto ary_idx : ary_idx_list->items)
    {
        assert(ary_idx != nullptr && "array indexer (or funcall) is null when it should not be");
        ary_idx->accept(this);
    }
}

void codegen_visitor::visit(array_index* ary_idx)
{
    auto expr_list = ary_idx->index_expression_list;
    auto type = ary_idx->type;
    switch(type)
    {
    case array_index_type::ARRAY_OR_FUNCALL:
        assert(false && "unresolved array or funcall type");
    break;
    case array_index_type::ARRAY_CELL:
    case array_index_type::ARRAY:
        out << "[";
        expr_list->accept(this);
        out << "]";
    break;
    case array_index_type::FUNCALL:
        out << "(";
        expr_list->accept(this);
        out << ")";
    break;
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
    typedef vector<postfix_op>::const_iterator transpose_iter;
    auto expr = post_expr->expr;
    const auto& tp_list = post_expr->transposes;

    function<void(transpose_iter)> tp = [&](transpose_iter here) {
        if(here == tp_list.end())
            expr->accept(this);
        else
        {
            switch((*here))
            {
            case postfix_op::TRANSPOSE: 
                out << "t(";
                tp(here + 1);
                out << ")";
            break;
            case postfix_op::NCTRANSPOSE: /* TODO */ break;
            }
        }
    };
    tp(tp_list.cbegin());
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
    {
        auto cols = prim_expr->array;
        if(cols->size() == 0) out << "NULL";
        else if(cols->size() == 1)
        {
            out << "c(";
            cols->accept(this);
            out << ")";
        }
        else
        {
            size_t colsize = cols->size();
            size_t rowsize = (*cols->begin())->size();
            out << "matrix(c(";
            cols->accept(this);
            out << "), " << colsize << ", " << rowsize << ")";
        }
    }
    break;
    case primary_expression_type::CELL_ARRAY:
    {
        auto cols = prim_expr->array;
        if(cols->size() == 0) out << "NULL";
        else if(cols->size() == 1)
        {
            out << "list(";
            cols->accept(this);
            out << ")";
        }
        else
        {
            size_t colsize = cols->size();
            size_t rowsize = (*cols->begin())->size();
            out << "matrix(list(";
            cols->accept(this);
            out << "), " << colsize << ", " << rowsize << ")";
        }
    }
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
void codegen_visitor::visit(array_col_list* col_list)
{
    for(auto iter = col_list->begin(); iter != col_list->end(); iter++)
    {
        auto col = *iter;
        col->accept(this);
        if(iter + 1 != col_list->end())
            out << ", ";
    }
}
void codegen_visitor::visit(array_row_list* row_list)
{
    for(auto iter = row_list->begin(); iter != row_list->end(); iter++)
    {
        auto row = *iter;
        row->accept(this);
        if(iter + 1 != row_list->end())
            out << ", ";
    }
}
void codegen_visitor::visit(index_expression* idx_expr)
{
    if(idx_expr->is_colon_op)
    {
        // TODO: colon operator, aka select all
    }
    else
    {
        auto expr = idx_expr->expr;
        assert(expr != nullptr && "index expression is null when it should not be");
        expr->accept(this);
    }
}
void codegen_visitor::visit(index_expression_list* expr_list)
{
    for(auto iter = expr_list->begin(); iter != expr_list->end(); iter++)
    {
        (*iter)->accept(this);
        if(iter + 1 != expr_list->end())
            out << ", ";
    }
}

void codegen_visitor::visit(function_declare* fundecl)
{
    fun_return_stack.push(fundecl->returns);
    out << fundecl->name << " <- function (" << pad_commas(fundecl->args) << ") {" << endl;

    indent++;
    fundecl->statement_list->accept(this);

    print_indent();
    size_t ret_count = fun_return_stack.top().size();
    if(ret_count > 1)
        out << "c(" << pad_commas(fun_return_stack.top()) << ")";
    else if(ret_count == 1)
        out << *(fun_return_stack.top().cbegin());
    out << endl;

    indent--;

    out << "}" << endl;
    fun_return_stack.pop();
}
void codegen_visitor::visit(catch_statement* catch_stmt)
{
    auto stmt_list = catch_stmt->statement_list;
    auto ident = catch_stmt->identifier;
    out << "function(" << ident << ") {" << endl;
    indent++;
    stmt_list->accept(this);
    indent--;
    print_indent();
    out << "}";
}
void codegen_visitor::visit(try_statement* try_stmt)
{
    auto stmt_list = try_stmt->statement_list;
    auto catch_stmt = try_stmt->catch_statement;
    if(catch_stmt != nullptr)
        out << "tryCatch({" << endl;
    else
        out << "try({" << endl;
    indent++;
    stmt_list->accept(this);
    indent--;
    print_indent();
    out << "}";
    if(catch_stmt != nullptr)
    {
        out << ", error = ";
        catch_stmt->accept(this);
    }
    out << ")";
}
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
        out << "return(" << pad_commas(fun_return_stack.top()) << ")";
    break;
    }
}
/* void codegen_visitor::visit(global_statement*) { } */
void codegen_visitor::visit(clear_statement* clear_stmt)
{
    const auto& id_list = clear_stmt->identifier_list;
    out << "rm(list=";
    if(id_list.size() == 0)
        out << "setdiff(ls(), lsf.str())";
    else
        out << "intersect(c(" << pad_commas<map_wrap_quotes>(id_list) << "), setdiff(ls(), lsf.str()))";
    out << ")";
}
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
void codegen_visitor::visit(switch_statement* switch_stmt)
{
    auto expr = switch_stmt->expression;
    auto case_list = switch_stmt->case_list;
    auto otherwise_stmt = switch_stmt->otherwise_statement;
    assert(expr != nullptr && "expression in switch statement must not be null");

    for(auto case_iter = case_list->begin(); case_iter != case_list->end(); case_iter++)
    {
        auto case_ptr = *case_iter;
        out << "if (";
        expr->accept(this);
        out << " == ";
        // TODO : assert this isn't nullptr
        case_ptr->condition->accept(this);
        out << ") {" << endl;
        indent++;
        case_ptr->statement_list->accept(this);
        indent--;
        print_indent();
        out << "} ";
        if(case_iter + 1 != case_list->end() || otherwise_stmt != nullptr)
            out << "else ";
    }

    if(otherwise_stmt != nullptr)
    {
        out << "{" << endl;
        indent++;
        otherwise_stmt->statement_list->accept(this);
        indent--;
        print_indent();
        out << "}";
    }
}
// void codegen_visitor::visit(case_statement* case_stmt) { }
// void codegen_visitor::visit(otherwise_statement*) { }

void codegen_visitor::visit(statement_list* stmt_list)
{
    for(auto stmt : stmt_list->items)
    {
        print_indent();
        stmt->accept(this);
        out << endl;
    }
}
