/**
 * This file is used by the AST to include generator AST items. AST generator
 * items are not generated using the parser, rather, they are used to represent
 * language constructs that R has, which MATLAB does not. These are dropped in
 * place of the old AST items, and have their own specific methods for code
 * generation, et al.
 */

#ifndef AST_GENERATOR_HPP
#define AST_GENERATOR_HPP

#ifndef AST_HPP
#error This file cannot be included standalone. Please include ast.hpp instead.
#endif

namespace ast
{

#include "ast/generator/funcall_arg_assign.hpp"

} /* namespace ast */

#endif /* AST_GENERATOR_HPP */