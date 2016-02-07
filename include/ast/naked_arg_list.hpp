#ifndef AST_NAKED_ARG_LIST_HPP
#define AST_NAKED_ARG_LIST_HPP

#include <memory>
#include <vector>
#include <string>
#include "types.hpp"

namespace ast
{


class naked_arg_list
    : public node
{ 
public:
    naked_arg_list() = default;
    virtual ~naked_arg_list() = default;

    std::vector<std::string> args;

    void add_front(cstref item) { args.insert(args.begin(), item); }

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_NAKED_ARG_LIST_HPP */