#ifndef VISITOR_CODEGEN_VISITOR
#define VISITOR_CODEGEN_VISITOR

#ifndef VISITOR_HPP
#error This file should not be included standalone. Please include visitor.hpp instead.
#endif

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
    virtual void visit(ast::case_statement*);
    virtual void visit(ast::otherwise_statement*);
    virtual void visit(ast::statement_list*);

private:
    std::ostream& out;
    size_t indent;
    std::stack<fun_return_list> fun_return_stack;
    std::unordered_set<std::string> function_names;

    void print_indent() { for(size_t i = 0; i < indent; i++) out << "   "; }
};

#endif