#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <memory>

namespace ast
{


class node
{
public:
    virtual ~node() = default;
    virtual void accept(visitor_p visitor) = 0;
    virtual void children_accept(visitor_p guest) = 0;
    virtual void traverse_top_down(visitor_p guest) = 0;
    virtual void traverse_bottom_up(visitor_p guest) = 0;
};

}; /* Namespace AST */

#endif /* AST_NODE_HPP */