#ifndef AST_ASSIGNMENT_STATEMENT_HPP
#define AST_ASSIGNMENT_STATEMENT_HPP

#include <memory>

namespace ast
{

class assignment_statement
    : public statement
{
public:
    typedef statement base_t;
    
public:
    assignment_statement(assignment_expression_p expression) 
        : expression(expression) { }
    virtual ~assignment_statement() = default;

    assignment_expression_p expression;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_ASSIGNMENT_STATEMENT_HPP */