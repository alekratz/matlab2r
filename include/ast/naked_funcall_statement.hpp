#ifndef AST_NAKED_FUNCALL_STATEMENT_HPP
#define AST_NAKED_FUNCALL_STATEMENT_HPP

#include <memory>

namespace ast
{

class naked_funcall_statement
    : public statement
{
public:
    typedef statement base_t;

public:
    naked_funcall_statement(cstref identifier, cstref first, identifier_list_p args) 
        : identifier(identifier)
        , args(args->identifiers) 
            { add_front(first); }
    naked_funcall_statement(cstref identifier) 
        : identifier(identifier) { }
    virtual ~naked_funcall_statement() = default;

    std::string identifier;
    std::vector<std::string> args;

    void add_front(cstref arg) { args.insert(args.begin(), arg); }

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest) { }
    virtual void traverse_top_down(visitor_p guest) { accept(guest); }
    virtual void traverse_bottom_up(visitor_p guest) { accept(guest); }
};

} /* namespace ast */

#endif /* AST_NAKED_FUNCALL_STATEMENT_HPP */