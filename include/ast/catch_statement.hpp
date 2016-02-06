#ifndef AST_CATCH_STATEMENT_HPP
#define AST_CATCH_STATEMENT_HPP

#include <memory>

namespace ast
{

class catch_statement;
typedef std::shared_ptr<catch_statement> catch_statement_p;

class catch_statement
    : public block_statement
{ 
public:
    typedef block_statement base_t;

public:
    catch_statement(statement_list_p statements, std::string identifier="")
        : base_t(statements)
        , identifier(identifier) { }
    virtual ~catch_statement() = default;

    std::string identifier;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_CATCH_STATEMENT_HPP */