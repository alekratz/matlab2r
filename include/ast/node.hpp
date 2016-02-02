#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <memory>

namespace ast
{

class node;
typedef std::shared_ptr<node> node_p;

class node
{
public:
    virtual ~node() = default;
    virtual void accept(visitor_p visitor) = 0;
};

}; /* Namespace AST */

#endif /* AST_NODE_HPP */