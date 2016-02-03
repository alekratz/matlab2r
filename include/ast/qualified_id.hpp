#ifndef AST_QUALIFIED_ID
#define AST_QUALIFIED_ID

#include <memory>
#include <vector>

namespace ast
{

class qualified_id;
typedef std::shared_ptr<qualified_id> qualified_id_p;

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
    virtual void children_accept(visitor_p guest)
    {
        for(auto item : items)
            item->accept(guest);
    }
    virtual void traverse_top_down(visitor_p guest)
    {
        accept(guest);
        for(auto item : items)
            item->traverse_top_down(guest);
    }
    virtual void traverse_bottom_up(visitor_p guest)
    { 
        for(auto item : items)
            item->traverse_bottom_up(guest);
        accept(guest);
    }
};

};

#endif /* AST_UNARY_OP */