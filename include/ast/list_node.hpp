#ifndef AST_LIST_NODE_HPP
#define AST_LIST_NODE_HPP

#include <memory>
#include <vector>

namespace ast
{

template<typename wrapped>
class list_node :
    public node
{
public:
    typedef std::shared_ptr<wrapped> wrapped_p;

public:
    list_node() = default;
    virtual ~list_node() = default;
    
    std::vector<wrapped_p> items;

    void add_front(wrapped_p item) { items.insert(items.begin(), item); }
    size_t size() { return items.size(); }
    auto begin() { return items.begin(); }
    auto end() { return items.end(); }

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_LIST_NODE_HPP */