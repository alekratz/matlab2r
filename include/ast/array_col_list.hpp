#ifndef AST_ARRAY_COL_LIST_HPP
#define AST_ARRAY_COL_LIST_HPP

#include <memory>

namespace ast
{

class array_col_list;
typedef std::shared_ptr<array_col_list> array_col_list_p;

class array_col_list
{
public:
    array_col_list() = default;
    virtual ~array_col_list() = default;
    
    std::vector<array_col_list_p> rows;

    void add_front(array_col_list_p op) { rows.insert(rows.begin(), op); }

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_ARRAY_COL_LIST_HPP */