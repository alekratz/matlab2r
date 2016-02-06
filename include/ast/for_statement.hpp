#ifndef AST_FOR_STATEMENT_HPP
#define AST_FOR_STATEMENT_HPP

#include <memory>

namespace ast
{

class for_statement;
typedef std::shared_ptr<for_statement> for_statement_p;

class for_statement
    : public block_statement
{
public:
    typedef block_statement base_t;

public:
    for_statement(std::string variable, expression_p range) : variable(variable), range(range) { }
    virtual ~for_statement() = default;

    std::string variable;
    expression_p range;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_FOR_STATEMENT_HPP */