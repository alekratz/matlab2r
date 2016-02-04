#include "ast.hpp"

namespace ast
{
void naked_arg_list::children_accept(visitor_p) { }
void naked_arg_list::traverse_top_down(visitor_p guest) {  accept(guest); }
void naked_arg_list::traverse_bottom_up(visitor_p guest) { accept(guest); }
}