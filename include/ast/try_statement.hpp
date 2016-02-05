#ifndef AST_TRY_STATEMENT_HPP
#define AST_TRY_STATEMENT_HPP

#include <memory>

namespace ast
{

class try_statement;
typedef std::shared_ptr<try_statement> try_statement_p;

class try_statement
    : public node
{ 
public:
    try_statement() = default;
    //try_statement(statement_list_p statements, catch_statement_p catch_statement=nullptr)
    virtual ~try_statement() = default;

    //std::vector<statement_list_p> statements;
    catch_statement_p catch_statement;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_TRY_STATEMENT_HPP */