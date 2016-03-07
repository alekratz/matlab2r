#ifndef VISITOR_FUNCTION_NAME_VISITOR_HPP
#define VISITOR_FUNCTION_NAME_VISITOR_HPP

#ifndef VISITOR_HPP
#error This file should not be included standalone. Please include visitor.hpp instead.
#endif

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

#endif