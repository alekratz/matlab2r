#ifndef AST_SWITCH_STATEMENT_HPP
#define AST_SWITCH_STATEMENT_HPP

#include <memory>

namespace ast
{

class switch_statement
    : public statement
{
public:
    typedef statement base_t;

public:
    switch_statement(expression_p expression, statement_list_p statements, case_list_p case_list,
            otherwise_statement_p otherwise_statement)
        : base_t()
		, expression(expression)
		, case_list(case_list)
		, otherwise_statement(otherwise_statement) { }
		
    virtual ~switch_statement() = default;

    expression_p expression;
	case_list_p case_list;
	otherwise_statement_p otherwise_statement;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_SWITCH_STATEMENT_HPP */