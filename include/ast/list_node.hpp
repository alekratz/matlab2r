#ifndef AST_LIST_NODE_HPP
#define AST_LIST_NODE_HPP

#include <memory>
#include <vector>

namespace ast
{

template <typename wrapped>
class list_node;
class expression;
class index_expression;

/* List node types */
typedef list_node<expression> array_row_list;
typedef std::shared_ptr<array_row_list> array_row_list_p;
typedef list_node<array_row_list> array_col_list;
typedef std::shared_ptr<array_col_list> array_col_list_p;
typedef list_node<index_expression> index_expression_list;
typedef std::shared_ptr<index_expression_list> index_expression_list_p;

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

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_LIST_NODE_HPP */