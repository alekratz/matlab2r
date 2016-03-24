#include "visitor.hpp"
#include "ast.hpp"

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

void function_name_visitor::visit(qualified_id* qual_id)
{
    // None of the function names we're dealing with are only one item long
    if(qual_id->items.size() != 1)
        return;
    auto item = (*qual_id->items.begin());
    assert(item != nullptr);

    // only concerning identifiers
    if(item->type != qualified_id_item_type::IDENTIFIER || item->array_index_list == nullptr 
        || item->array_index_list->size() == 0)
        return;
    // is it contained?
    if(fname_map.count(item->identifier) != 0)
    {
        auto array_index = (*item->array_index_list->begin());
        if(array_index->type == array_index_type::ARRAY || array_index->type == array_index_type::ARRAY_CELL)
            return;
        auto item_ptr = item.get();
        fname_map[item->identifier](item_ptr);
    }
}

void function_name_visitor::init_fname_map()
{
    fname_map["helpbrowser"] =
    fname_map["doc"] =      [](qualified_id_item*& in) {
        in->identifier = "help.start";
    };
    fname_map["lookfor"] =  [](qualified_id_item*& in) {
        in->identifier = "help.search";
    };
    fname_map["linspace"] = [](qualified_id_item*& in) {
        in->identifier = "seq";
        auto funcall_args = (*in->array_index_list->begin())->index_expression_list;
        if(funcall_args->size() != 3)
        {
            cerr << "WARNING: invalid number of arguments to 'linspace': got " << funcall_args->size() << ", expected 3" 
                << endl;
            return;
        }
        
    };
}