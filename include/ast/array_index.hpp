#ifndef AST_ARRAY_INDEX_HPP
#define AST_ARRAY_INDEX_HPP

namespace ast
{

enum class array_index_type
{
    ARRAY_OR_FUNCALL,
    ARRAY_CELL,
};

class array_index
    : public node
{
public:
    typedef node base_t;
public:
    array_index(index_expression_list_p index_expression_list, array_index_type type)
        : index_expression_list(index_expression_list)
        , type(type)
        { }

    index_expression_list_p index_expression_list;
    array_index_type type;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

}

#endif