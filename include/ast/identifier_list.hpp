#ifndef AST_IDENTIFIER_LIST_HPP
#define AST_IDENTIFIER_LIST_HPP

#include <vector>
#include <string>
#include "types.hpp"

namespace ast
{

class identifier_list
    : public node
{
public:
    typedef node base_t;
public:
    identifier_list(cstref first) { add_front(first); };
    virtual ~identifier_list() = default;

    std::vector<std::string> identifiers;

    void add_front(cstref item) { identifiers.insert(identifiers.begin(), item); }

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest) { }
    virtual void traverse_top_down(visitor_p guest) { accept(guest); }
    virtual void traverse_bottom_up(visitor_p guest) { accept(guest); }
};

}

#endif /* AST_IDENTIFIER_LIST_HPP */