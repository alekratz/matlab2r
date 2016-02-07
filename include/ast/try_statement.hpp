#ifndef AST_TRY_STATEMENT_HPP
#define AST_TRY_STATEMENT_HPP

#include <memory>

namespace ast
{


class try_statement
    : public block_statement
{ 
public:
    typedef block_statement base_t;

public:
    try_statement(statement_list_p statements, catch_statement_p catch_statement=nullptr)
        : base_t(statements)
        , catch_statement(catch_statement) { }
    virtual ~try_statement() = default;
    
    catch_statement_p catch_statement;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_TRY_STATEMENT_HPP */