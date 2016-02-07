#include "ast.hpp"

namespace ast
{

void try_statement::children_accept(visitor_p guest)
{
    statement_list->accept(guest);
    catch_statement->accept(guest);
}

void try_statement::traverse_top_down(visitor_p guest)
{
    accept(guest);
    statement_list->traverse_top_down(guest);
    catch_statement->traverse_top_down(guest);
}

void try_statement::traverse_bottom_up(visitor_p guest)
{
    catch_statement->traverse_bottom_up(guest);
    statement_list->traverse_bottom_up(guest);
    accept(guest);
}

}