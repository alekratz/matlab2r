#ifndef AST_ITERATION_STATEMENT_HPP
#define AST_ITERATION_STATEMENT_HPP

#include <memory>

namespace ast
{

class iteration_statement;
typedef std::shared_ptr<iteration_statement> iteration_statement_p;

class iteration_statement
    : public node
{
public:
    typedef node base_t;

public:
    iteration_statement() = default;
    virtual ~iteration_statement() = default;

    //statement_list_p statement_list;

public:
    virtual void accept(visitor_p guest) = 0;
    virtual void children_accept(visitor_p guest) = 0;
    virtual void traverse_top_down(visitor_p guest) = 0;
    virtual void traverse_bottom_up(visitor_p guest) = 0;
};

} /* namespace ast */

#endif /* AST_ARRAY_COL_LIST_HPP */