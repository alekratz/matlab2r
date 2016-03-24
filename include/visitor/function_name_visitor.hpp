#ifndef VISITOR_FUNCTION_NAME_VISITOR_HPP
#define VISITOR_FUNCTION_NAME_VISITOR_HPP

#ifndef VISITOR_HPP
#error This file should not be included standalone. Please include visitor.hpp instead.
#endif

typedef std::function<void(ast::qualified_id_item*&)> fname_mapper_t;
typedef std::unordered_set<std::string> fname_set_t;
typedef std::unordered_map<std::string, fname_mapper_t> fname_map_t;

/**
 * This visitor gets a list of all function names used in the program. This is
 * used to help the code generator differentiate between matrix indexing and
 * function calls (because they are ambiguous).
 *
 * It also helps with translating function names. Not all functions in R and
 * MATLAB translate cleanly, and this class exists to help with that.
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
    virtual void visit(ast::qualified_id*);

    const std::unordered_set<std::string>& get_function_names() const 
        { return function_names; }

private:
    /**
     * Contains all of the function name mapping methods, and assigns them to the appropriate function name
     */
    void init_fname_map();

    fname_set_t function_names;
    fname_map_t fname_map;
};

#endif