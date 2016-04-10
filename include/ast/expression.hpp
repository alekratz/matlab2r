#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cassert>

namespace ast
{

enum class expression_op
{
    COLON,
    VBAR,
    AMP,
    EQ_OP,
    NE_OP,
    LT_OP,
    GT_OP,
    LE_OP,
    GE_OP,
    PLUS,
    MINUS,
    TIMES,
    FSLASH,
    BSLASH,
    POW,
    AMUL,
    ADIV,
    ARDIV,
    APOW,
    NONE,
};


class expression
    : public node
{
public:
    expression(primary_expression_p expr) 
        : lhs(nullptr)
        , op(expression_op::NONE)
        , rhs(nullptr)
        , expr(expr) { }
    expression(expression_p lhs, expression_op op, expression_p rhs) 
        : lhs(lhs)
        , op(op)
        , rhs(rhs) 
        , expr(nullptr) { assert(op != expression_op::NONE && "operator for expression must exist with a defined left hand side"); }
    virtual ~expression() = default;
    
    expression_p lhs;
    expression_op op;
    expression_p rhs;

    primary_expression_p expr;
public:
    virtual void accept(visitor_p guest);
    virtual void children_accept(visitor_p guest);
    virtual void traverse_top_down(visitor_p guest);
    virtual void traverse_bottom_up(visitor_p guest);

public:
    template<typename T>
    static expression_p build(T val)
        { return std::make_shared<expression>(std::make_shared<primary_expression>(val)); }
    
    static expression_p build_identifier(cstref val)
        { return std::make_shared<expression>(std::make_shared<primary_expression>(
            std::make_shared<qualified_id>(
            std::make_shared<qualified_id_item>(val)))); }

    static expression_p build_function(cstref fname, std::initializer_list<expression_p> args) {
        auto result = build_identifier(fname);
        auto qid_item = (*result->expr->qualified_id->items.begin());  // this is made by the build_identifier function
        qid_item->array_index_list = qualified_id_item::build_args(args);
        return result;
    }
};

};

#endif