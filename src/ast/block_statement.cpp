#include "ast.hpp"

namespace ast
{

// Implemented virtual destructor
block_statement::~block_statement() { }

void block_statement::children_accept(visitor_p guest)
    { statement_list->children_accept(guest); }

void block_statement::traverse_top_down(visitor_p guest)
    { statement_list->traverse_top_down(guest); }

void block_statement::traverse_bottom_up(visitor_p guest)
    { statement_list->traverse_bottom_up(guest); }

}