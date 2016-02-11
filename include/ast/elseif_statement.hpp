#ifndef AST_ELSEIF_STATEMENT_HPP
#define AST_ELSEIF_STATEMENT_HPP

#include <memory>

namespace ast
{

class elseif_statement
    : public block_statement
{
public:
    typedef block_statement base_t;

public:
    elseif_statement(expression_p condition, statement_list_p statements)
        : base_t(statements)
        , condition(condition) { }
    virtual ~elseif_statement() = default;

    expression_p condition;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_ELSEIF_STATEMENT_HPP */