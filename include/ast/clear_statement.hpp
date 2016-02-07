#ifndef AST_CLEAR_STATEMENT_HPP
#define AST_CLEAR_STATEMENT_HPP

#include <memory>
#include "types.hpp"

namespace ast
{


class clear_statement
    : public statement
{ 
public:
    typedef statement base_t;

public:
    clear_statement() = default;
    clear_statement(identifier_list_p identifier_list)
        : identifier_list(identifier_list->identifiers) { }
    virtual ~clear_statement() = default;

    std::vector<std::string> identifier_list;

    void add_front(cstref identifier) { identifier_list.insert(identifier_list.begin(), identifier); }

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest) { }
    virtual void traverse_top_down(visitor_p guest) { accept(guest); }
    virtual void traverse_bottom_up(visitor_p guest) { accept(guest); }
};

} /* namespace ast */

#endif /* AST_CLEAR_STATEMENT_HPP */