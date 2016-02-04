#ifndef AST_INDEX_EXPRESSION_LIST_HPP
#define AST_INDEX_EXPRESSION_LIST_HPP

#include <memory>

namespace ast
{

class index_expression_list;
typedef std::shared_ptr<index_expression_list> index_expression_list_p;

class index_expression_list
    : public list_node<index_expression>
{
public:
    index_expression_list() = default;
    virtual ~index_expression_list() = default;
};

} /* namespace ast */

#endif /* AST_INDEX_EXPRESSION_LIST_HPP */