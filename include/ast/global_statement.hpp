#ifndef AST_GLOBAL_STATEMENT_HPP
#define AST_GLOBAL_STATEMENT_HPP

#include <memory>

namespace ast
{

class global_statement;
typedef std::shared_ptr<global_statement> global_statement_p;

class global_statement
    : public statement
{ 
public:
    typedef statement base_t;

public:
    global_statement(global_statement_type type) : type(type) { }
    virtual ~global_statement() = default;

    std::vector<std::string> identifier_list;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest) { }
    virtual void traverse_top_down(visitor_p guest) { accept(guest); }
    virtual void traverse_bottom_up(visitor_p guest) { accept(guest); }
};

} /* namespace ast */

#endif /* AST_GLOBAL_STATEMENT_HPP */