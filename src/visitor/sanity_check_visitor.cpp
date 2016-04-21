#include "visitor.hpp"
#include "ast.hpp"

using namespace std;
using namespace ast;

sanity_check_visitor::sanity_check_visitor(ostream& out)
    : status(sanity_check_status::NOT_STARTED)
    , out(out)
    { }

void sanity_check_visitor::start(statement_list* ast)
{
    status = sanity_check_status::IN_PROGRESS;
    ast->traverse_top_down(this);
    if(status != sanity_check_status::ERROR)
        status = sanity_check_status::SUCCESS;
}
    
void sanity_check_visitor::visit(primary_expression* primary_expr)
{
    switch(primary_expr->type) {
    case primary_expression_type::MATRIX:
    {
        // make sure all of the array rows have the same dimensions
        if(primary_expr->array->size() == 0)
            return;
        size_t row_dim = (*primary_expr->array->begin())->size();
        for(auto row : primary_expr->array->items) {
            if(row_dim != row->size()) {
                out << "mismatched matrix rows (established " << row_dim << " vs. " << row->size() << ")" << endl;
                status = sanity_check_status::ERROR;
            }
        }
    }
    break;
    case primary_expression_type::CELL_ARRAY:
    {
        if(primary_expr->array->size() > 1) {
            out << "cell array is not allowed to have multiple columns" << endl;
            status = sanity_check_status::ERROR;
        }
    }
    break;
    default:
    return;
    }
}