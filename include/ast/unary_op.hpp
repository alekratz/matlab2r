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
        : type(type) { }
    virtual ~unary_op() = default;
    unary_op_type type;

public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest) { }
    virtual void traverse_top_down(visitor_p guest) { accept(guest); };
    virtual void traverse_bottom_up(visitor_p guest) { accept(guest); };
};

};

#endif /* AST_UNARY_OP */