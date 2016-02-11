#ifndef AST_FUNCTION_DECLARE_HPP
#define AST_FUNCTION_DECLARE_HPP

#include <memory>

namespace ast
{

class function_declare
    : public block_statement
{
public:
    typedef block_statement base_t;

public:
    function_declare(identifier_list_p returns, cstref name, identifier_list_p args, statement_list_p body)
        : base_t(body)
        , returns(returns->identifiers)
        , name(name)
        , args(args->identifiers) { }
    function_declare(cstref name, identifier_list_p args, statement_list_p body)
        : base_t(body)
        , name(name)
        , args(args->identifiers) { }
    virtual ~function_declare() = default;

    std::vector<std::string> returns;
    std::string name;
    std::vector<std::string> args;
    

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);
};

} /* namespace ast */

#endif /* AST_FUNCTION_DECLARE_HPP */