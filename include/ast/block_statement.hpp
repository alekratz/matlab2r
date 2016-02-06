#ifndef AST_BLOCK_STATEMENT_HPP
#define AST_BLOCK_STATEMENT_HPP

#include <memory>

namespace ast
{

class block_statement;
typedef std::shared_ptr<block_statement> block_statement_p;

class block_statement
    : public statement
{
public:
    typedef node base_t;

public:
    block_statement() = default;
    virtual ~block_statement() = default;

    //statement_list_p statement_list;

public:
    virtual void accept(visitor_p guest) = 0;
    virtual void children_accept(visitor_p guest) = 0;
    virtual void traverse_top_down(visitor_p guest) = 0;
    virtual void traverse_bottom_up(visitor_p guest) = 0;
};

} /* namespace ast */

#endif /* AST_BLOCK_STATEMENT_HPP */