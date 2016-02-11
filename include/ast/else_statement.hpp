#ifndef AST_ELSE_STATEMENT
#define AST_ELSE_STATEMENT

namespace ast
{

class else_statement;
typedef std::shared_ptr<else_statement> else_statement_p;

class else_statement : public block_statement
{ 
public:
    else_statement(statement_list_p statement_list)
        : block_statement(statement_list) { }
};

}

#endif /* AST_ELSE_STATEMENT */