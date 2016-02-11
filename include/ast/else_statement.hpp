#ifndef AST_ELSE_STATEMENT
#define AST_ELSE_STATEMENT

namespace ast
{

class else_statement;
typedef std::shared_ptr<else_statement> else_statement_p;

class else_statement : public block_statement
{ 
public:
    typedef block_statement base_t;

public:
    else_statement(statement_list_p statement_list)
        : block_statement(statement_list) { }

    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);  
};

}

#endif /* AST_ELSE_STATEMENT */