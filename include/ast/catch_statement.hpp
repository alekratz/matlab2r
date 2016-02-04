#ifndef AST_CATCH_STATEMENT_HPP
#define AST_CATCH_STATEMENT_HPP

#include <memory>

namespace ast
{

class catch_statement;
typedef std::shared_ptr<catch_statement> catch_statement_p;

class catch_statement
    : public node
{ 
public:
    catch_statement() = default;
    //catch_statement(statement_list_p statements, std::string identifier="")
    virtual ~catch_statement() = default;

    //std::vector<statement_list_p> statements;
    std::string identifier;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_ARRAY_COL_LIST_HPP */