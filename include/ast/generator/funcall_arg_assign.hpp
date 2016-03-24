#ifndef AST_GENERATOR_FUNCALL_ARG_ASSIGN
#define AST_GENERATOR_FUNCALL_ARG_ASSIGN

namespace generator
{

class funcall_arg_assign
    : public node
{
public:
    funcall_arg_assign(cstref lhs, expression_p rhs) 
        : lhs(lhs)
        , rhs(rhs) { }
    virtual ~funcall_arg_assign() = default;
    
    std::string lhs;
    expression_p rhs;

public:
    virtual void accept(visitor_p guest) { }
    virtual void children_accept(visitor_p guest) { }
    virtual void traverse_top_down(visitor_p guest) { }
    virtual void traverse_bottom_up(visitor_p guest) { }
};

} /* namespace generator */
#endif /* AST_GENERATOR_FUNCALL_ARG_ASSIGN */