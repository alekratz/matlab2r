#ifndef AST_QUALIFIED_ID_ITEM
#define AST_QUALIFIED_ID_ITEM

#include <memory>
#include <string>

namespace ast
{

typedef std::shared_ptr<index_expression_list> index_expression_list_p;

class qualified_id_item
    : public node
{
public:
    qualified_id_item()
        : expression(nullptr)
        , array_or_funcall_tail(nullptr)
        , array_cell_tail(nullptr) 
        { }
    virtual ~qualified_id_item() = default;
    
    expression_p expression;
    index_expression_list_p array_or_funcall_tail;
    index_expression_list_p array_cell_tail;

public:
    std::string identifier;
    bool has_tail() { return array_or_funcall_tail != nullptr || array_cell_tail != nullptr; }
    bool is_expression() { return expression != nullptr; }

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest) { /* TODO */ }
    virtual void traverse_top_down(visitor_p guest) { accept(guest); }
    virtual void traverse_bottom_up(visitor_p guest) { accept(guest); }
};

};

#endif /* AST_UNARY_OP */