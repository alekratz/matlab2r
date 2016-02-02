#ifndef AST_HPP
#define AST_HPP

#include <memory>

/* Forward declaration of the visitor class */
class visitor;
typedef std::shared_ptr<visitor> visitor_p;

#include "ast/node.hpp"
#include "ast/unary_op.hpp"


/* Include visitor at the end so all classes have access to it */
#include "visitor.hpp"
#endif