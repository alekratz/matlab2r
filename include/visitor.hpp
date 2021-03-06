#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "ast.hpp"
#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>

class visitor
{
public:
    virtual ~visitor() = default;

public:
    virtual void visit(ast::qualified_id*) { }
    virtual void visit(ast::qualified_id_item*) { }
    virtual void visit(ast::array_index*) { }
    virtual void visit(ast::array_index_list*) { }
    virtual void visit(ast::assignment_expression*) { }
    virtual void visit(ast::expression*) { }
    virtual void visit(ast::unary_expression*) { }
    virtual void visit(ast::postfix_expression*) { }
    virtual void visit(ast::primary_expression*) { }
    virtual void visit(ast::array_col_list*) { }
    virtual void visit(ast::array_row_list*) { }
    virtual void visit(ast::index_expression*) { }
    virtual void visit(ast::index_expression_list*) { }
    virtual void visit(ast::function_declare*) { }
    virtual void visit(ast::catch_statement*) { }
    virtual void visit(ast::try_statement*) { }
    virtual void visit(ast::for_statement*) { }
    virtual void visit(ast::while_statement*) { }
    virtual void visit(ast::jump_statement*) { }
    virtual void visit(ast::global_statement*) { }
    virtual void visit(ast::clear_statement*) { }
    virtual void visit(ast::expression_statement*) { }
    virtual void visit(ast::assignment_statement*) { }
    virtual void visit(ast::naked_funcall_statement*) { }
    virtual void visit(ast::identifier_list*) { }
    virtual void visit(ast::if_statement*) { }
    virtual void visit(ast::elseif_list*) { }
    virtual void visit(ast::elseif_statement*) { }
    virtual void visit(ast::else_statement*) { }
	virtual void visit(ast::switch_statement*) { }
	virtual void visit(ast::case_list*) { }
	virtual void visit(ast::case_statement*) { }
	virtual void visit(ast::otherwise_statement*) { }
    virtual void visit(ast::statement_list*) { }
};

/**
 * This visitor gets a list of all function names used in the program. This is
 * used to help the code generator differentiate between matrix indexing and
 * function calls (because they are ambiguous).
 */
class function_name_visitor
    : public visitor
{
public:
    function_name_visitor();
    virtual ~function_name_visitor() = default;

public:
    virtual void visit(ast::function_declare*);
    virtual void visit(ast::statement_list*);

    const std::unordered_set<std::string>& get_function_names() const 
        { return function_names; }

private:
    std::unordered_set<std::string> function_names;
};

class rename_visitor
    : public visitor
{
public:
    rename_visitor();
    virtual ~rename_visitor() = default;

public:
    // virtual void visit(ast::qualified_id*) { }
    // virtual void visit(ast::qualified_id_item*) { }
    // virtual void visit(ast::array_index*) { }
    // virtual void visit(ast::array_index_list*) { }
    // virtual void visit(ast::assignment_expression*) { }
    // virtual void visit(ast::expression*) { }
    // virtual void visit(ast::unary_expression*) { }
    // virtual void visit(ast::postfix_expression*) { }
    // virtual void visit(ast::primary_expression*) { }
    // virtual void visit(ast::array_col_list*) { }
    // virtual void visit(ast::array_row_list*) { }
    // virtual void visit(ast::index_expression*) { }
    // virtual void visit(ast::index_expression_list*) { }
    // virtual void visit(ast::function_declare*) { }
    // virtual void visit(ast::catch_statement*) { }
    // virtual void visit(ast::try_statement*) { }
    // virtual void visit(ast::for_statement*) { }
    // virtual void visit(ast::while_statement*) { }
    // virtual void visit(ast::jump_statement*) { }
    // virtual void visit(ast::global_statement*) { }
    // virtual void visit(ast::clear_statement*) { }
    // virtual void visit(ast::expression_statement*) { }
    // virtual void visit(ast::assignment_statement*) { }
    // virtual void visit(ast::naked_funcall_statement*) { }
    // virtual void visit(ast::identifier_list*) { }
    // virtual void visit(ast::if_statement*) { }
    // virtual void visit(ast::elseif_list*) { }
    // virtual void visit(ast::elseif_statement*) { }
    // virtual void visit(ast::else_statement*) { }
    // virtual void visit(ast::switch_statement*) { }
    // virtual void visit(ast::case_list*) { }
    // virtual void visit(ast::case_statement*) { }
    // virtual void visit(ast::otherwise_statement*) { }
    // virtual void visit(ast::statement_list*) { }
};

/**
 * This visitor ensures that the MATLAB code plugged in is sane. This includes:
 *     * Matrix dimensions
 */
class sanity_check_visitor
    : public visitor
{
public:
    sanity_check_visitor();
    virtual ~sanity_check_visitor() = default;

public:
    // virtual void visit(ast::qualified_id*) { }
    // virtual void visit(ast::qualified_id_item*) { }
    // virtual void visit(ast::array_index*) { }
    // virtual void visit(ast::array_index_list*) { }
    // virtual void visit(ast::assignment_expression*) { }
    // virtual void visit(ast::expression*) { }
    // virtual void visit(ast::unary_expression*) { }
    // virtual void visit(ast::postfix_expression*) { }
    // virtual void visit(ast::primary_expression*) { }
    // virtual void visit(ast::array_col_list*) { }
    // virtual void visit(ast::array_row_list*) { }
    // virtual void visit(ast::index_expression*) { }
    // virtual void visit(ast::index_expression_list*) { }
    // virtual void visit(ast::function_declare*) { }
    // virtual void visit(ast::catch_statement*) { }
    // virtual void visit(ast::try_statement*) { }
    // virtual void visit(ast::for_statement*) { }
    // virtual void visit(ast::while_statement*) { }
    // virtual void visit(ast::jump_statement*) { }
    // virtual void visit(ast::global_statement*) { }
    // virtual void visit(ast::clear_statement*) { }
    // virtual void visit(ast::expression_statement*) { }
    // virtual void visit(ast::assignment_statement*) { }
    // virtual void visit(ast::naked_funcall_statement*) { }
    // virtual void visit(ast::identifier_list*) { }
    // virtual void visit(ast::if_statement*) { }
    // virtual void visit(ast::elseif_list*) { }
    // virtual void visit(ast::elseif_statement*) { }
    // virtual void visit(ast::else_statement*) { }
    // virtual void visit(ast::switch_statement*) { }
    // virtual void visit(ast::case_list*) { }
    // virtual void visit(ast::case_statement*) { }
    // virtual void visit(ast::otherwise_statement*) { }
    // virtual void visit(ast::statement_list*) { }
};

class codegen_visitor
    : public visitor
{
private:
    typedef std::vector<std::string> fun_return_list;

public:
    codegen_visitor(std::unordered_set<std::string> function_names);
    virtual ~codegen_visitor() = default;

public:
    virtual void visit(ast::qualified_id*);
    virtual void visit(ast::qualified_id_item*);
    virtual void visit(ast::array_index*);
    virtual void visit(ast::array_index_list*);
    virtual void visit(ast::assignment_expression*);
    virtual void visit(ast::expression*);
    virtual void visit(ast::unary_expression*);
    virtual void visit(ast::postfix_expression*);
    virtual void visit(ast::primary_expression*);
    virtual void visit(ast::array_col_list*);
    virtual void visit(ast::array_row_list*);
    virtual void visit(ast::index_expression*);
    virtual void visit(ast::index_expression_list*);
    virtual void visit(ast::function_declare*);
    virtual void visit(ast::catch_statement*);
    virtual void visit(ast::try_statement*);
    virtual void visit(ast::for_statement*);
    virtual void visit(ast::while_statement*);
    virtual void visit(ast::jump_statement*);
    // virtual void visit(ast::global_statement*);
    virtual void visit(ast::clear_statement*);
    virtual void visit(ast::expression_statement*);
    virtual void visit(ast::assignment_statement*);
    virtual void visit(ast::naked_funcall_statement*);
    // virtual void visit(ast::identifier_list*);
    virtual void visit(ast::if_statement*);
    virtual void visit(ast::elseif_statement*);
    virtual void visit(ast::else_statement*);
    virtual void visit(ast::switch_statement*);
    //virtual void visit(ast::case_statement*);
    //virtual void visit(ast::otherwise_statement*);
    virtual void visit(ast::statement_list*);

private:
    std::ostream& out;
    size_t indent;
    std::stack<fun_return_list> fun_return_stack;
    std::unordered_set<std::string> function_names;

    void print_indent() { for(size_t i = 0; i < indent; i++) out << "   "; }
};

typedef visitor* visitor_p;

#endif