#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "ast.hpp"
#include <memory>
#include <iostream>

class visitor
{
public:
    virtual ~visitor() = default;

public:
    virtual void visit(ast::qualified_id*) { }
    virtual void visit(ast::qualified_id_item*) { }
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

class print_visitor
    : public visitor
{
public:
    virtual ~print_visitor() = default;

public:
    virtual void visit(ast::qualified_id*) { std::cout << "qualified_id" << std::endl; }
    virtual void visit(ast::qualified_id_item*) { std::cout << "qualified_id_item" << std::endl; }
    virtual void visit(ast::assignment_expression*) { std::cout << "assignment_expression" << std::endl; }
    virtual void visit(ast::expression*) { std::cout << "expression" << std::endl; }
    virtual void visit(ast::unary_expression*) { std::cout << "unary_expression" << std::endl; }
    virtual void visit(ast::postfix_expression*) { std::cout << "postfix_expression" << std::endl; }
    virtual void visit(ast::primary_expression*) { std::cout << "primary_expression" << std::endl; }
    virtual void visit(ast::array_col_list*) { std::cout << "array_col_list" << std::endl; }
    virtual void visit(ast::array_row_list*) { std::cout << "array_row_list" << std::endl; }
    virtual void visit(ast::index_expression*) { std::cout << "index_expression" << std::endl; }
    virtual void visit(ast::index_expression_list*) { std::cout << "index_expression_list" << std::endl; }
    virtual void visit(ast::function_declare* fundecl) 
        { 
            std::cout <<    "function_declare" << std::endl <<
                            "    returns : " << [&]() { std::string s; for(auto f : fundecl->returns) s += f + " "; return s; }() << std::endl <<
                            "    name    : " << fundecl->name << std::endl <<
                            "    args    : " << [&]() { std::string s; for(auto f : fundecl->args) s += f + " "; return s; }() << std::endl;
        }
    virtual void visit(ast::catch_statement*) { std::cout << "catch_statement" << std::endl; }
    virtual void visit(ast::try_statement*) { std::cout << "try_statement" << std::endl; }
    virtual void visit(ast::for_statement*) { std::cout << "for_statement" << std::endl; }
    virtual void visit(ast::while_statement*) { std::cout << "while_statement" << std::endl; }
    virtual void visit(ast::jump_statement*) { std::cout << "jump_statement" << std::endl; }
    virtual void visit(ast::global_statement*) { std::cout << "global_statement" << std::endl; }
    virtual void visit(ast::clear_statement*) { std::cout << "clear_statement" << std::endl; }
    virtual void visit(ast::expression_statement*) { std::cout << "expression_statement" << std::endl; }
    virtual void visit(ast::assignment_statement*) { std::cout << "assignment_statement" << std::endl; }
    virtual void visit(ast::naked_funcall_statement*) { std::cout << "naked_funcall_statement" << std::endl; }
    virtual void visit(ast::identifier_list*) { std::cout << "identifier_list" << std::endl; }
    virtual void visit(ast::if_statement*) { std::cout << "if_statement" << std::endl; }
    virtual void visit(ast::elseif_list*) { std::cout << "elseif_list" << std::endl; }
    virtual void visit(ast::elseif_statement*) { std::cout << "elseif_statement" << std::endl; }
    virtual void visit(ast::else_statement*) { std::cout << "else_statement" << std::endl; }
    virtual void visit(ast::switch_statement*) { std::cout << "switch_statement" << std::endl; }
    virtual void visit(ast::case_list*) { std::cout << "case_list" << std::endl; }
    virtual void visit(ast::case_statement*) { std::cout << "case_statement" << std::endl; }
    virtual void visit(ast::otherwise_statement*) { std::cout << "otherwise_statement" << std::endl; }
    
};

class codegen_visitor
    : public visitor
{
public:
    codegen_visitor();
    virtual ~codegen_visitor() = default;

public:
    virtual void visit(ast::qualified_id*) { }
    virtual void visit(ast::qualified_id_item*) { }
    virtual void visit(ast::assignment_expression*) { }
    virtual void visit(ast::expression*) { }
    virtual void visit(ast::unary_expression*) { }
    virtual void visit(ast::postfix_expression*) { }
    virtual void visit(ast::primary_expression*) { }
    virtual void visit(ast::array_col_list*) { }
    virtual void visit(ast::array_row_list*) { }
    virtual void visit(ast::index_expression*) { }
    virtual void visit(ast::index_expression_list*) { }
    virtual void visit(ast::function_declare*);
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

private:
    std::ostream& out;
    size_t indent;

    std::string make_indent();
};

typedef visitor* visitor_p;

#endif