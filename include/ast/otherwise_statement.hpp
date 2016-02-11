#ifndef AST_OTHERWISE_STATEMENT_HPP
#define AST_OTHERWISE_STATEMENT_HPP

#include <memory>

namespace ast
{

class otherwise_statement
    : public block_statement
{
public:
    typedef block_statement base_t;

public:
    otherwise_statement(statement_list_p statements)
        : base_t(statements) { }
    virtual ~otherwise_statement() = default;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_OTHERWISE_STATEMENT_HPP */