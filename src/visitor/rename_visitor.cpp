#include "visitor.hpp"
#include "ast.hpp"

using namespace std;
using namespace ast;

rename_visitor::rename_visitor()
{ }

void rename_visitor::visit(ast::qualified_id_item* qid_item)
{
    if(qid_item->type != qualified_id_item_type::IDENTIFIER) return;
    static const char* r = ".";

    for(size_t replace = qid_item->identifier.find("_"); replace != string::npos; replace = qid_item->identifier.find("_"))
        qid_item->identifier.replace(replace, 1, r);
}

void rename_visitor::visit(ast::statement_list* stmt_list)
{
    for(auto stmt : stmt_list->items)
        stmt->traverse_top_down(this);
}