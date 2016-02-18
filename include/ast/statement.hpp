#ifndef AST_STATEMENT_HPP
#define AST_STATEMENT_HPP

#include <memory>

namespace ast
{

class statement
    : public node
{
public:
    typedef node base_t;

public:
    statement() = default;
    virtual ~statement() = default;

public:
    virtual void accept(visitor_p guest) = 0;
    virtual void children_accept(visitor_p guest) = 0;
    virtual void traverse_top_down(visitor_p guest) = 0;
    virtual void traverse_bottom_up(visitor_p guest) = 0;
};

} /* namespace ast */

#endif /* AST_STATEMENT_HPP */