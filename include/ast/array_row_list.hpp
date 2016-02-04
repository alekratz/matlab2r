#ifndef AST_ARRAY_ROW_LIST_HPP
#define AST_ARRAY_ROW_LIST_HPP

#include <memory>

namespace ast
{

class array_row_list;
typedef std::shared_ptr<array_row_list> array_row_list_p;
class expression;
typedef std::shared_ptr<expression> expression_p;

class array_row_list
    : public list_node<expression>
{
public:
    array_row_list() = default;
    virtual ~array_row_list() = default;
    
public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_ARRAY_COL_LIST_HPP */