#ifndef AST_ARRAY_COL_LIST_HPP
#define AST_ARRAY_COL_LIST_HPP

#include <memory>

namespace ast
{

class array_col_list;
typedef std::shared_ptr<array_col_list> array_col_list_p;

class array_col_list
    : public list_node<array_row_list>
{
public:
    array_col_list() = default;
    virtual ~array_col_list() = default;
};

} /* namespace ast */

#endif /* AST_ARRAY_COL_LIST_HPP */