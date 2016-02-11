#ifndef AST_IF_STATEMENT_HPP
#define AST_IF_STATEMENT_HPP

#include <memory>

namespace ast
{

class if_statement
    : public block_statement
{
public:
    typedef block_statement base_t;

public:
    if_statement(expression_p condition, statement_list_p statements, elseif_list_p elseif_list,
            else_statement_p else_statement)
        : base_t(statements)
        , condition(condition)
        , elseif_list(elseif_list)
        , else_statement(else_statement) { }
    virtual ~if_statement() = default;

    expression_p condition;
    elseif_list_p elseif_list;
    else_statement_p else_statement;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_IF_STATEMENT_HPP */