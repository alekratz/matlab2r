#ifndef AST_WHILE_STATEMENT_HPP
#define AST_WHILE_STATEMENT_HPP

#include <memory>

namespace ast
{

class while_statement;
typedef std::shared_ptr<while_statement> while_statement_p;

class while_statement
    : public iteration_statement
{
public:
    typedef iteration_statement base_t;

public:
    while_statement(expression_p condition) : condition(condition) { }
    virtual ~while_statement() = default;

    expression_p condition;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_ARRAY_COL_LIST_HPP */