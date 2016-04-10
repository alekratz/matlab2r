#ifndef AST_QUALIFIED_ID_ITEM
#define AST_QUALIFIED_ID_ITEM

#include <memory>
#include <string>
#include "types.hpp"

namespace ast
{

typedef std::shared_ptr<index_expression_list> index_expression_list_p;

enum class qualified_id_item_type
{
    EXPRESSION,
    IDENTIFIER,
};

class qualified_id_item
    : public node
{
public:
    qualified_id_item(expression_p expression)
        : expression(expression)
        , array_index_list(nullptr)
        , type(qualified_id_item_type::EXPRESSION)
        { }
    qualified_id_item(cstref identifier)
        : identifier(identifier)
        , array_index_list(nullptr)
        , type(qualified_id_item_type::IDENTIFIER)
        { }
    virtual ~qualified_id_item() = default;
    
    expression_p expression;
    std::string identifier;
    array_index_list_p array_index_list;

    qualified_id_item_type type;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest) {  }
    virtual void traverse_top_down(visitor_p guest) { accept(guest); }
    virtual void traverse_bottom_up(visitor_p guest) { accept(guest); }

public:
    static array_index_list_p build_args(std::initializer_list<expression_p> args)
    {
        auto result = std::make_shared<ast::array_index_list>(); // some jackass used this as a member name already
        auto idx_expr_list = std::make_shared<index_expression_list>();
        auto array_idx = std::make_shared<array_index>(idx_expr_list, array_index_type::FUNCALL);
        for(auto expr : args) {
            idx_expr_list->items.push_back(std::make_shared<index_expression>(expr));
        }
        result->add_front(array_idx);

        return result;
    }
};

};

#endif /* AST_UNARY_OP */