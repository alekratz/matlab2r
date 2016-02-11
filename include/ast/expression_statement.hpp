#ifndef AST_EXPRESSION_STATEMENT_HPP
#define AST_EXPRESSION_STATEMENT_HPP

#include <memory>

namespace ast
{

class expression_statement
    : public statement
{
public:
    typedef statement base_t;
    
public:
    expression_statement(expression_p expression) 
        : expression(expression) { }
    virtual ~expression_statement() = default;

    expression_p expression;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_EXPRESSION_STATEMENT_HPP */