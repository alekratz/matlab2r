#ifndef AST_UNARY_OP
#define AST_UNARY_OP

#include <memory>

namespace ast
{

class unary_op;
typedef std::shared_ptr<unary_op> unary_op_p;

/* c-style enum intended. These are glorified macros, and they're short and sweet. */
enum unary_op_type
{
    PLUS,
    MINUS,
    TILDE,
    NONE,
};

class unary_op
    : public node
{
public:
    unary_op(unary_op_type type)
    : type(type)
        { }
    unary_op_type type;
    virtual void accept(visitor_p guest);
};

};

#endif /* AST_UNARY_OP */