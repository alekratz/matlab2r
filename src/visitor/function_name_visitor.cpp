#include "visitor.hpp"
#include "ast.hpp"
#include <iostream>
#include <string>

using namespace ast;
using namespace std;

function_name_visitor::function_name_visitor()
{
    init_fname_map();
}

void function_name_visitor::visit(function_declare* fundecl)
    { function_names.insert(fundecl->name); }

void function_name_visitor::visit(ast::statement_list* stmt_list)
{
    for(auto stmt : stmt_list->items)
        stmt->traverse_top_down(this);
}

void function_name_visitor::visit(ast::expression* expr)
{
    auto prim_expr = expr->expr;
    if(expr->op == expression_op::NONE && prim_expr->type == primary_expression_type::QUALIFIED_ID) {
        auto qual_id = prim_expr->qualified_id;
        // We only care about single-shot qualified IDs
        if(qual_id->items.size() != 1) return;
        auto& qual_id_item = *qual_id->items.begin();
        // We only care about identifiers (this check may not be necessary)
        if(qual_id_item->type != qualified_id_item_type::IDENTIFIER) return;
        // We only care about function calls
        auto array_indices = qual_id_item->array_index_list;
        if(array_indices == nullptr) return;
        if(array_indices->size() == 0) return;
        // Finally, check to see if it's a function we care about. If it is, then we will call its mapper function.
        auto mapper = fname_map.find(qual_id_item->identifier);
        if(mapper != fname_map.end()) {
            auto array_index = (*qual_id_item->array_index_list->begin());
            array_index->type = array_index_type::FUNCALL;
            fname_map[qual_id_item->identifier](expr, qual_id_item.get());
        }
    }
}

void function_name_visitor::init_fname_map()
{
    fname_map["linspace"] = [](expression* expr, qualified_id_item* item) {
        auto args = (*item->array_index_list->begin())->index_expression_list;
        if(args->size() != 3) { 
            cerr << "error: unable to convert linspace function to seq function, "
                    "incorrect number of arguments (got " << args->size() << " vs 3). skipping" << endl;
            return;
        }
        item->identifier = "seq";
        auto rhs = args->items[2]->expr; // TODO : colon operator
        args->items[2]->expr = nullptr;
        args->items[2]->named_expr = make_shared<generator::funcall_arg_assign>("len", rhs);
    };

    fname_map["logspace"] = [](expression* expr, qualified_id_item* item) {
        auto args = (*item->array_index_list->begin())->index_expression_list;
        if(args->size() != 3) { 
            cerr << "error: unable to convert logspace function to seq function, "
                    "incorrect number of arguments (got " << args->size() << " vs 3). skipping" << endl;
            return;
        }
        
        expr->lhs = expression::build(10.0);
        expr->op = expression_op::POW;

        item->identifier = "seq";
        auto rhs = args->items[2]->expr;
        args->items[2]->expr = nullptr;
        args->items[2]->named_expr = make_shared<generator::funcall_arg_assign>("len", rhs);
        expr->rhs = make_shared<expression>(expr->expr);
        expr->expr = nullptr;
    };
}