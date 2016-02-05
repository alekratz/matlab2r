#ifndef AST_JUMP_STATEMENT_HPP
#define AST_JUMP_STATEMENT_HPP

#include <memory>

namespace ast
{

class jump_statement;
typedef std::shared_ptr<jump_statement> jump_statement_p;

enum class jump_statement_type
{
    BREAK,
    CONTINUE,
    RETURN,
};

class jump_statement
    : public node
{ 
public:
    jump_statement(jump_statement_type type) : type(type) { }
    virtual ~jump_statement() = default;

    jump_statement_type type;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest) { }
    virtual void traverse_top_down(visitor_p guest) { accept(guest); }
    virtual void traverse_bottom_up(visitor_p guest) { accept(guest); }
};

} /* namespace ast */

#endif /* AST_JUMP_STATEMENT_HPP */