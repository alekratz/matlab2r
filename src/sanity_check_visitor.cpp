#include "visitor.hpp"
#include "ast.hpp"

using namespace std;
using namespace ast;

sanity_check_visitor::sanity_check_visitor()
    : status(sanity_check_status::NOT_STARTED)
    { }

void sanity_check_visitor::start(statement_list* ast)
{
    
}
    
void sanity_check_visitor::visit(primary_expression* primary_expr)
{
    switch(primary_expr->type) {
    case primary_expression_type::MATRIX:
    {
        // make sure all of the array rows have the same dimensions
        for(auto col : primary_expr->array->items) {
            
        }
    }
    break;
    case primary_expression_type::CELL_ARRAY:
    {
    }
    break;
    default:
    return;
    }
}