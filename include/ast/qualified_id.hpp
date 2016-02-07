#ifndef AST_QUALIFIED_ID
#define AST_QUALIFIED_ID

#include <memory>
#include <vector>

namespace ast
{

class qualified_id
    : public node
{
public:
    qualified_id() = default;
    qualified_id(qualified_id_item_p initial_item)
        { add_front(initial_item); }
    
    virtual ~qualified_id() = default;
    void add_front(qualified_id_item_p item) { items.insert(items.begin(), item); }
    std::vector<qualified_id_item_p> items;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

};

#endif /* AST_UNARY_OP */