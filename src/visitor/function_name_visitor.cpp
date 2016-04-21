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
    /* 
        The source I'm using for matlab to R https://cran.r-project.org/doc/contrib/Hiebeler-matlabR.pdf
    */
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

    fname_map["ones"] = fname_map["zeros"] = [](expression* expr, qualified_id_item* item) {
        auto args = (*item->array_index_list->begin())->index_expression_list;
        expression_p rows = nullptr, cols = nullptr;
        assert(item->identifier == "ones" || item->identifier == "zeros");
        expression_p value = (item->identifier == "ones")
            ? expression::build(1.0)
            : expression::build(0.0);

        if(args->size() == 1) {
            if(args->items[0]->is_colon_op) {
                cerr << "error: unable to convert ones/zeros function to matrix function, "
                        "colon op used when expression expected. skipping" << endl;
                return;
            }
            rows = cols = args->items[0]->expr;
        }
        else if(args->size() == 2) {
            if(args->items[0]->is_colon_op || args->items[1]->is_colon_op) {
                cerr << "error: unable to convert ones/zeros function to matrix function, "
                        "colon op used when expression expected. skipping" << endl;
                return;
            }
            rows = args->items[0]->expr;
            cols = args->items[1]->expr;
        }
        else if(args->size() == 0) {
            expr->expr = make_shared<primary_expression>(0.0);
            return;
        }
        else {
            cerr << "error: unsupported number of arguments for ones/zeros function "
                    "(" << args->size() << "). skipping" << endl;
            return;
        }

        assert(rows != nullptr && cols != nullptr);

        /* 
        so the source I'm using (noted in comments above) makes a distinction
        between when MATLAB uses zeros(1, n) and zeros(m, n); the former
        having a translation to a vector (using R's rep() function) and the
        latter having a translation to a matrix. I don't think this is a good
        idea - matrices vs. vectors have different behaviors in R. I want for
        matrices to stay matrices, and vectors to stay vectors.
        */

        // make the matrix definition
        item->identifier = "matrix";
        while(args->size() < 3) {
            auto idx_expr = make_shared<index_expression>();
            idx_expr->is_colon_op = false;
            args->items.push_back(idx_expr);
        }
        args->items[0]->expr = value;
        args->items[1]->named_expr = make_shared<generator::funcall_arg_assign>("nrow", rows);
        args->items[2]->named_expr = make_shared<generator::funcall_arg_assign>("ncol", cols);
        args->items[1]->expr = args->items[2]->expr = nullptr;
    };

    fname_map["eye"] = [](expression* expr, qualified_id_item* item) {
        auto args = (*item->array_index_list->begin())->index_expression_list;
        if(args->size() == 1) {
            if(args->items[0]->is_colon_op) {
                cerr << "error: unable to convert eye function to diag function, "
                        "colon op used when expression expected. skipping" << endl;
                return;
            }
        }
        else if(args->size() == 2) {
            if(args->items[0]->is_colon_op || args->items[1]->is_colon_op) {
                cerr << "error: unable to convert eye function to diag function, "
                        "colon op used when expression expected. skipping" << endl;
                return;
            }
        }
        else {
            cerr << "error: unable to convert eye function to diag function, "
                    "incorrect number of arguments (expected 1 or 2 vs. " <<
                    args->size() << "). skipping" << endl;
            return;
        }
        // double check that we're not dealing with a colon op
        for(auto arg : args->items) {
            if(arg->is_colon_op) {
                cerr << "error: unable to convert eye function to diag function, "
                        "colon op used when expression expected. skipping" << endl;
            }
        }
        // insert a final named argument that specifies that the value should be
        // one. In matlab, you multiply by X, which is valid in R as well.
        auto one = expression::build(1.0);
        auto x_named_arg = make_shared<generator::funcall_arg_assign>("x", one);
        args->items.push_back(make_shared<index_expression>(x_named_arg));
        item->identifier = "diag";
    };

    fname_map["fliplr"] = [](expression* expr, qualified_id_item* item) {
        auto args = (*item->array_index_list->begin())->index_expression_list;
        if(args->size() != 1) {
            cerr << "error: unable to convert fliplr function to t(apply()) function, "
                    "incorrect number of arguments (expected 1 vs. " << 
                    args->size() << "). skipping" << endl;
            return;
        }

        // fliplr(A) -> t(apply(A, 1, rev))
        auto rev_ident = expression::build_identifier("rev");
        auto one = expression::build(1.0);
        auto apply_func_expr = expression::build_function("apply", { args->items[0]->expr, one, rev_ident });

        item->identifier = "t";
        item->array_index_list = qualified_id_item::build_args({ apply_func_expr });
    };

    fname_map["flipud"] = [](expression* expr, qualified_id_item* item) {
        auto args = (*item->array_index_list->begin())->index_expression_list;
        if(args->size() != 1) {
            cerr << "error: unable to convert flipud function to apply() function, "
                    "incorrect number of arguments (expected 1 vs. " << 
                    args->size() << "). skipping" << endl;
            return;
        }

        // flipup(A) -> apply(A, 2, rev)
        auto first_arg = args->items[0]->expr; // this is necessary because args[0] gets reset and thus becomes invalidated
        auto two = expression::build(2.0);
        auto rev_ident = expression::build_identifier("rev");

        item->identifier = "apply";
        item->array_index_list = qualified_id_item::build_args({ first_arg, two, rev_ident });
    };
    // The "diag" method works by itself just fine, so we'll just define it to do nothing so it gets labeled as a function
    fname_map["diag"] = [](expression* expr, qualified_id_item* item) {};

    
}