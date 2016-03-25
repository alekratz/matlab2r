#include "matlab2r_driver.hpp"
#include "ast.hpp"
#include <string>
#define BOOST_TEST_MODULE test_parser
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace ast;

#define AUTO_REQUIRE(A, B) auto A = B; \
    BOOST_REQUIRE(A != nullptr)
#define EXPR_TO_PRIMARY(E) AUTO_REQUIRE(primary_ ## E, E->expr)
; // this is here to keep me from going insane

BOOST_AUTO_TEST_CASE(test_function_declare)
{
    matlab2r_driver the_driver;
    // function declare statement with no returns or parameters
    BOOST_REQUIRE(the_driver.parse_string(
        string(
        "function test_funcall()\n"
        "   123\n"
        "end"),
        "test"
    ));
    auto ast = the_driver.ast;
    BOOST_REQUIRE(ast->size() == 1);
    AUTO_REQUIRE(fundecl_stmt, dynamic_pointer_cast<function_declare>(*ast->begin()));
    BOOST_CHECK(fundecl_stmt->returns.size() == 0);
    BOOST_CHECK(fundecl_stmt->args.size() == 0);
    BOOST_CHECK(fundecl_stmt->statement_list->size() == 1);
    BOOST_CHECK(fundecl_stmt->name == "test_funcall");
    AUTO_REQUIRE(constant_stmt, dynamic_pointer_cast<expression_statement>(*fundecl_stmt->statement_list->begin()));
    AUTO_REQUIRE(constant, constant_stmt->expression);
    BOOST_REQUIRE(constant->op == expression_op::NONE);
    EXPR_TO_PRIMARY(constant);
    BOOST_CHECK(primary_constant->type == primary_expression_type::CONSTANT);
    BOOST_CHECK(primary_constant->constant == 123.0);
}

BOOST_AUTO_TEST_CASE(test_function_declare_rets_no_params)
{
    matlab2r_driver the_driver;
    // function declare statement with returns, but no parameters
    BOOST_REQUIRE(the_driver.parse_string(
        string(
        "function [a, b] = test_funcall()\n"
        "   123\n"
        "end"),
        "test"
    ));
    auto ast = the_driver.ast;
    BOOST_REQUIRE(ast->size() == 1);
    AUTO_REQUIRE(fundecl_stmt, dynamic_pointer_cast<function_declare>(*ast->begin()));
    BOOST_REQUIRE(fundecl_stmt->returns.size() == 2);
    BOOST_CHECK(fundecl_stmt->args.size() == 0);
    BOOST_CHECK(fundecl_stmt->returns[0] == "a");
    BOOST_CHECK(fundecl_stmt->returns[1] == "b");
    BOOST_CHECK(fundecl_stmt->statement_list->size() == 1);
    BOOST_CHECK(fundecl_stmt->name == "test_funcall");
    AUTO_REQUIRE(constant_stmt, dynamic_pointer_cast<expression_statement>(*fundecl_stmt->statement_list->begin()));
    AUTO_REQUIRE(constant, constant_stmt->expression);
    BOOST_REQUIRE(constant->op == expression_op::NONE);
    EXPR_TO_PRIMARY(constant);
    BOOST_CHECK(primary_constant->type == primary_expression_type::CONSTANT);
    BOOST_CHECK(primary_constant->constant == 123.0);
}

BOOST_AUTO_TEST_CASE(test_function_declare_params_no_rets)
{
    matlab2r_driver the_driver;
    // function declare statement without returns, but with parameters
    BOOST_REQUIRE(the_driver.parse_string(
        string(
        "function test_funcall(c, d)\n"
        "   123\n"
        "end"),
        "test"
    ));
    auto ast = the_driver.ast;
    BOOST_REQUIRE(ast->size() == 1);
    AUTO_REQUIRE(fundecl_stmt, dynamic_pointer_cast<function_declare>(*ast->begin()));
    BOOST_CHECK(fundecl_stmt->returns.size() == 0);
    BOOST_REQUIRE(fundecl_stmt->args.size() == 2);
    BOOST_CHECK(fundecl_stmt->args[0] == "c");
    BOOST_CHECK(fundecl_stmt->args[1] == "d");
    BOOST_CHECK(fundecl_stmt->statement_list->size() == 1);
    BOOST_CHECK(fundecl_stmt->name == "test_funcall");
    AUTO_REQUIRE(constant_stmt, dynamic_pointer_cast<expression_statement>(*fundecl_stmt->statement_list->begin()));
    AUTO_REQUIRE(constant, constant_stmt->expression);
    BOOST_REQUIRE(constant->op == expression_op::NONE);
    EXPR_TO_PRIMARY(constant);
    BOOST_CHECK(primary_constant->type == primary_expression_type::CONSTANT);
    BOOST_CHECK(primary_constant->constant == 123.0);
}

BOOST_AUTO_TEST_CASE(test_function_declare_params_and_rets)
{
    matlab2r_driver the_driver;
    // function declare statement with both returns and parameters
    BOOST_REQUIRE(the_driver.parse_string(
        string(
        "function [a, b] = test_funcall(c, d)\n"
        "   123\n"
        "end"),
        "test"
    ));
    auto ast = the_driver.ast;
    BOOST_REQUIRE(ast->size() == 1);
    AUTO_REQUIRE(fundecl_stmt, dynamic_pointer_cast<function_declare>(*ast->begin()));
    BOOST_REQUIRE(fundecl_stmt->returns.size() == 2);
    BOOST_REQUIRE(fundecl_stmt->args.size() == 2);
    BOOST_CHECK(fundecl_stmt->returns[0] == "a");
    BOOST_CHECK(fundecl_stmt->returns[1] == "b");
    BOOST_CHECK(fundecl_stmt->args[0] == "c");
    BOOST_CHECK(fundecl_stmt->args[1] == "d");
    BOOST_CHECK(fundecl_stmt->statement_list->size() == 1);
    BOOST_CHECK(fundecl_stmt->name == "test_funcall");
    AUTO_REQUIRE(constant_stmt, dynamic_pointer_cast<expression_statement>(*fundecl_stmt->statement_list->begin()));
    AUTO_REQUIRE(constant, constant_stmt->expression);
    BOOST_REQUIRE(constant->op == expression_op::NONE);
    EXPR_TO_PRIMARY(constant);
    BOOST_CHECK(primary_constant->type == primary_expression_type::CONSTANT);
    BOOST_CHECK(primary_constant->constant == 123.0);
}

BOOST_AUTO_TEST_CASE(test_global_statement_one_arg)
{
    matlab2r_driver the_driver;
    // global statement with one argument
    {
        BOOST_REQUIRE(the_driver.parse_string(
            string("global a\n"),
            "test"
        ));
        auto ast = the_driver.ast;
        BOOST_REQUIRE(ast->size() == 1);
        AUTO_REQUIRE(global_stmt, dynamic_pointer_cast<global_statement>(*ast->begin()));
        BOOST_REQUIRE(global_stmt->identifier_list.size() == 1);
        BOOST_CHECK(global_stmt->identifier_list[0] == "a");
    }
}

BOOST_AUTO_TEST_CASE(test_global_statement_many_args)
{
    matlab2r_driver the_driver;
    // global statement with many arguments
    {
        BOOST_REQUIRE(the_driver.parse_string(
            string("global a b c d\n"),
            "test"
        ));
        auto ast = the_driver.ast;
        BOOST_REQUIRE(ast->size() == 1);
        AUTO_REQUIRE(global_stmt, dynamic_pointer_cast<global_statement>(*ast->begin()));
        BOOST_REQUIRE(global_stmt->identifier_list.size() == 4);
        BOOST_CHECK(global_stmt->identifier_list[0] == "a");
        BOOST_CHECK(global_stmt->identifier_list[1] == "b");
        BOOST_CHECK(global_stmt->identifier_list[2] == "c");
        BOOST_CHECK(global_stmt->identifier_list[3] == "d");
    }
}

BOOST_AUTO_TEST_CASE(test_clear_statement_no_arg)
{
    matlab2r_driver the_driver;
    // clear statement with no argument
    {
        BOOST_REQUIRE(the_driver.parse_string(
            string("clear\n"),
            "test"
        ));
        auto ast = the_driver.ast;
        BOOST_REQUIRE(ast->size() == 1);
        AUTO_REQUIRE(clear_stmt, dynamic_pointer_cast<clear_statement>(*ast->begin()));
        BOOST_CHECK(clear_stmt->identifier_list.size() == 0);
    }
}

BOOST_AUTO_TEST_CASE(test_clear_statement_one_arg)
{
    matlab2r_driver the_driver;
    // clear statement with one argument
    {
        BOOST_REQUIRE(the_driver.parse_string(
            string("clear a\n"),
            "test"
        ));
        auto ast = the_driver.ast;
        BOOST_REQUIRE(ast->size() == 1);
        AUTO_REQUIRE(clear_stmt, dynamic_pointer_cast<clear_statement>(*ast->begin()));
        BOOST_REQUIRE(clear_stmt->identifier_list.size() == 1);
        BOOST_CHECK(clear_stmt->identifier_list[0] == "a");
    }
}

BOOST_AUTO_TEST_CASE(test_clear_statement_many_args)
{
    matlab2r_driver the_driver;
    // clear statement with many arguments
    {
        BOOST_REQUIRE(the_driver.parse_string(
            string("clear a b c d\n"),
            "test"
        ));
        auto ast = the_driver.ast;
        BOOST_REQUIRE(ast->size() == 1);
        AUTO_REQUIRE(clear_stmt, dynamic_pointer_cast<clear_statement>(*ast->begin()));
        BOOST_REQUIRE(clear_stmt->identifier_list.size() == 4);
        BOOST_CHECK(clear_stmt->identifier_list[0] == "a");
        BOOST_CHECK(clear_stmt->identifier_list[1] == "b");
        BOOST_CHECK(clear_stmt->identifier_list[2] == "c");
        BOOST_CHECK(clear_stmt->identifier_list[3] == "d");
    }
}

BOOST_AUTO_TEST_CASE(test_assignment_statement)
{
    matlab2r_driver the_driver;
    // basic assignment statement
    {
        BOOST_REQUIRE(the_driver.parse_string(
            string("a = b\n"),
            "test"
        ));
        auto ast = the_driver.ast;
        BOOST_REQUIRE(ast->size() == 1);
        AUTO_REQUIRE(assign_stmt, dynamic_pointer_cast<assignment_statement>(*ast->begin()));
        AUTO_REQUIRE(assign_expr, assign_stmt->expression);
        AUTO_REQUIRE(lhs, assign_expr->lhs);
        AUTO_REQUIRE(rhs, assign_expr->rhs);
        
        BOOST_CHECK(lhs->transposes.size() == 0);
        BOOST_REQUIRE(lhs->type == primary_expression_type::QUALIFIED_ID);
        AUTO_REQUIRE(qid_lhs, lhs->qualified_id);
        BOOST_REQUIRE(qid_lhs->items.size() == 1);
        AUTO_REQUIRE(qid_item_lhs, qid_lhs->items[0]);
        BOOST_REQUIRE(qid_item_lhs->type == qualified_id_item_type::IDENTIFIER);
        BOOST_CHECK(qid_item_lhs->identifier == "a");
        
        EXPR_TO_PRIMARY(rhs);
        BOOST_REQUIRE(primary_rhs->type == primary_expression_type::QUALIFIED_ID);
        AUTO_REQUIRE(qid_rhs, primary_rhs->qualified_id);
        BOOST_REQUIRE(qid_rhs->items.size() == 1);
        AUTO_REQUIRE(qid_item_rhs, qid_rhs->items[0]);
        BOOST_REQUIRE(qid_item_rhs->type == qualified_id_item_type::IDENTIFIER);
        BOOST_CHECK(qid_item_rhs->identifier == "b");
    }
}

BOOST_AUTO_TEST_CASE(test_assignment_statement_multiple)
{
    matlab2r_driver the_driver;
    // multi-assign statement
    {
        BOOST_REQUIRE(the_driver.parse_string(
            string("[a, b] = c\n"),
            "test"
        ));
        auto ast = the_driver.ast;
        BOOST_REQUIRE(ast->size() == 1);
        AUTO_REQUIRE(assign_stmt, dynamic_pointer_cast<assignment_statement>(*ast->begin()));
        AUTO_REQUIRE(assign_expr, assign_stmt->expression);
        AUTO_REQUIRE(lhs, assign_expr->lhs);
        AUTO_REQUIRE(rhs, assign_expr->rhs);
        
        BOOST_CHECK(lhs->transposes.size() == 0);
        BOOST_REQUIRE(lhs->type == primary_expression_type::MATRIX);
        AUTO_REQUIRE(array_lhs, lhs->array);
        BOOST_REQUIRE(array_lhs->items.size() == 1);
        BOOST_REQUIRE(array_lhs->items[0]->items.size() == 2);
        AUTO_REQUIRE(first_lhs, array_lhs->items[0]->items[0]);
        AUTO_REQUIRE(second_lhs, array_lhs->items[0]->items[1]);
        EXPR_TO_PRIMARY(first_lhs);
        EXPR_TO_PRIMARY(second_lhs);
        BOOST_REQUIRE(primary_first_lhs->type == primary_expression_type::QUALIFIED_ID);
        AUTO_REQUIRE(qid_first_lhs, primary_first_lhs->qualified_id);
        BOOST_REQUIRE(qid_first_lhs->items.size() == 1);
        AUTO_REQUIRE(qid_first_lhs_item, qid_first_lhs->items[0]);
        BOOST_REQUIRE(qid_first_lhs_item->type == qualified_id_item_type::IDENTIFIER);
        BOOST_CHECK(qid_first_lhs_item->identifier == "a");
        
        BOOST_REQUIRE(primary_second_lhs->type == primary_expression_type::QUALIFIED_ID);
        AUTO_REQUIRE(qid_second_lhs, primary_second_lhs->qualified_id);
        BOOST_REQUIRE(qid_second_lhs->items.size() == 1);
        AUTO_REQUIRE(qid_second_lhs_item, qid_second_lhs->items[0]);
        BOOST_REQUIRE(qid_second_lhs_item->type == qualified_id_item_type::IDENTIFIER);
        BOOST_CHECK(qid_second_lhs_item->identifier == "b");
        
        EXPR_TO_PRIMARY(rhs);
        BOOST_REQUIRE(primary_rhs->type == primary_expression_type::QUALIFIED_ID);
        AUTO_REQUIRE(qid_rhs, primary_rhs->qualified_id);
        BOOST_REQUIRE(qid_rhs->items.size() == 1);
        AUTO_REQUIRE(qid_item_rhs, qid_rhs->items[0]);
        BOOST_REQUIRE(qid_item_rhs->type == qualified_id_item_type::IDENTIFIER);
        BOOST_CHECK(qid_item_rhs->identifier == "c");
    }
}

BOOST_AUTO_TEST_CASE(test_if_statement)
{
    matlab2r_driver the_driver;
    // Basic IF statement
    BOOST_REQUIRE(the_driver.parse_string(
        string(
        "if a == b \n"
        "   'fun'\n"
        "end"), 
        "test"
    ));

    auto ast = the_driver.ast;
    BOOST_REQUIRE(ast->size() == 1);
    AUTO_REQUIRE(if_stmt, dynamic_pointer_cast<if_statement>(*ast->begin()));
    BOOST_CHECK(if_stmt->elseif_list->size() == 0);
    BOOST_CHECK(if_stmt->else_statement == nullptr);
    AUTO_REQUIRE(cond, dynamic_pointer_cast<expression>(if_stmt->condition));
    BOOST_REQUIRE(cond->op != expression_op::NONE);
    BOOST_CHECK(cond->op == expression_op::EQ_OP);
    AUTO_REQUIRE(lhs, cond->lhs);
    AUTO_REQUIRE(rhs, cond->rhs);
    EXPR_TO_PRIMARY(lhs);
    EXPR_TO_PRIMARY(rhs);
    BOOST_CHECK(primary_lhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_rhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_lhs->transposes.size() == 0);
    BOOST_CHECK(primary_rhs->transposes.size() == 0);
    AUTO_REQUIRE(qid_list_lhs, primary_lhs->qualified_id);
    AUTO_REQUIRE(qid_list_rhs, primary_rhs->qualified_id);
    AUTO_REQUIRE(qid_item_lhs, *qid_list_lhs->items.begin());
    AUTO_REQUIRE(qid_item_rhs, *qid_list_rhs->items.begin());
    BOOST_CHECK(qid_item_lhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(qid_item_rhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(qid_item_lhs->identifier == "a");
    BOOST_CHECK(qid_item_rhs->identifier == "b");

    AUTO_REQUIRE(if_block, if_stmt->statement_list);
    BOOST_REQUIRE(if_block->size() == 1);
    AUTO_REQUIRE(strlit_stmt, dynamic_pointer_cast<expression_statement>(*if_block->begin()));
    AUTO_REQUIRE(strlit, strlit_stmt->expression);
    EXPR_TO_PRIMARY(strlit);
    BOOST_CHECK(primary_strlit->type == primary_expression_type::STRING_LIT);
    BOOST_CHECK(primary_strlit->string_lit == "'fun'");
}

BOOST_AUTO_TEST_CASE(test_if_statement_with_elseif_else)
{
    matlab2r_driver the_driver;
    // Basic IF statement with ELSE and ELSEIF
    BOOST_REQUIRE(the_driver.parse_string(
        string(
        "if a == b \n"
        "   'fun'\n"
        "elseif c > d\n"
        "   'sorta fun'\n"
        "else\n"
        "   'not fun'\n"
        "end"), 
        "test"
    ));

    auto ast = the_driver.ast;
    BOOST_REQUIRE(ast->size() == 1);
    AUTO_REQUIRE(if_stmt, dynamic_pointer_cast<if_statement>(*ast->begin()));
    AUTO_REQUIRE(cond, dynamic_pointer_cast<expression>(if_stmt->condition));
    BOOST_REQUIRE(cond->op != expression_op::NONE);
    BOOST_CHECK(cond->op == expression_op::EQ_OP);
    AUTO_REQUIRE(lhs, cond->lhs);
    AUTO_REQUIRE(rhs, cond->rhs);
    EXPR_TO_PRIMARY(lhs);
    EXPR_TO_PRIMARY(rhs);
    BOOST_CHECK(primary_lhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_rhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_lhs->transposes.size() == 0);
    BOOST_CHECK(primary_rhs->transposes.size() == 0);
    AUTO_REQUIRE(qid_list_lhs, primary_lhs->qualified_id);
    AUTO_REQUIRE(qid_list_rhs, primary_rhs->qualified_id);
    AUTO_REQUIRE(qid_item_lhs, *qid_list_lhs->items.begin());
    AUTO_REQUIRE(qid_item_rhs, *qid_list_rhs->items.begin());
    BOOST_CHECK(qid_item_lhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(qid_item_rhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(qid_item_lhs->identifier == "a");
    BOOST_CHECK(qid_item_rhs->identifier == "b");

    AUTO_REQUIRE(if_block, if_stmt->statement_list);
    BOOST_REQUIRE(if_block->size() == 1);
    AUTO_REQUIRE(strlit_stmt, dynamic_pointer_cast<expression_statement>(*if_block->begin()));
    AUTO_REQUIRE(strlit, strlit_stmt->expression);
    EXPR_TO_PRIMARY(strlit);
    BOOST_CHECK(primary_strlit->type == primary_expression_type::STRING_LIT);
    BOOST_CHECK(primary_strlit->string_lit == "'fun'");

    BOOST_REQUIRE(if_stmt->elseif_list->size() == 1);
    AUTO_REQUIRE(elseif_stmt, (*if_stmt->elseif_list->begin()));
    AUTO_REQUIRE(elseif_cond, dynamic_pointer_cast<expression>(elseif_stmt->condition));
    BOOST_REQUIRE(elseif_cond->op != expression_op::NONE);
    BOOST_CHECK(elseif_cond->op == expression_op::GT_OP);
    AUTO_REQUIRE(elseif_lhs, elseif_cond->lhs);
    AUTO_REQUIRE(elseif_rhs, elseif_cond->rhs);
    EXPR_TO_PRIMARY(elseif_lhs);
    EXPR_TO_PRIMARY(elseif_rhs);
    BOOST_CHECK(primary_elseif_lhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_elseif_rhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_elseif_lhs->transposes.size() == 0);
    BOOST_CHECK(primary_elseif_rhs->transposes.size() == 0);
    AUTO_REQUIRE(elseif_qid_list_lhs, primary_elseif_lhs->qualified_id);
    AUTO_REQUIRE(elseif_qid_list_rhs, primary_elseif_rhs->qualified_id);
    AUTO_REQUIRE(elseif_qid_item_lhs, *elseif_qid_list_lhs->items.begin());
    AUTO_REQUIRE(elseif_qid_item_rhs, *elseif_qid_list_rhs->items.begin());
    BOOST_CHECK(elseif_qid_item_lhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(elseif_qid_item_rhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(elseif_qid_item_lhs->identifier == "c");
    BOOST_CHECK(elseif_qid_item_rhs->identifier == "d");

    AUTO_REQUIRE(else_stmt, if_stmt->else_statement);
    AUTO_REQUIRE(else_stmt_list, else_stmt->statement_list);
    BOOST_REQUIRE(else_stmt_list->size() == 1);
    AUTO_REQUIRE(strlit2_expr, dynamic_pointer_cast<expression_statement>(*else_stmt_list->begin()));
    AUTO_REQUIRE(strlit2, strlit2_expr->expression);
    EXPR_TO_PRIMARY(strlit2);
    BOOST_CHECK(primary_strlit2->type == primary_expression_type::STRING_LIT);
    BOOST_CHECK(primary_strlit2->string_lit == "'not fun'");
}

BOOST_AUTO_TEST_CASE(test_elseif_statement)
{
    matlab2r_driver the_driver;
    // Basic IF with ELSE statement
    BOOST_REQUIRE(the_driver.parse_string(
        string(
        "if a == b \n"
        "   'fun'\n"
        "elseif c > d\n"
        "   'sorta fun'\n"
        "end"), 
        "test"
    ));

    auto ast = the_driver.ast;
    BOOST_REQUIRE(ast->size() == 1);
    AUTO_REQUIRE(if_stmt, dynamic_pointer_cast<if_statement>(*ast->begin()));
    BOOST_CHECK(if_stmt->else_statement == nullptr);
    AUTO_REQUIRE(cond, dynamic_pointer_cast<expression>(if_stmt->condition));
    BOOST_REQUIRE(cond->op != expression_op::NONE);
    BOOST_CHECK(cond->op == expression_op::EQ_OP);
    AUTO_REQUIRE(lhs, cond->lhs);
    AUTO_REQUIRE(rhs, cond->rhs);
    EXPR_TO_PRIMARY(lhs);
    EXPR_TO_PRIMARY(rhs);
    BOOST_CHECK(primary_lhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_rhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_lhs->transposes.size() == 0);
    BOOST_CHECK(primary_rhs->transposes.size() == 0);
    AUTO_REQUIRE(qid_list_lhs, primary_lhs->qualified_id);
    AUTO_REQUIRE(qid_list_rhs, primary_rhs->qualified_id);
    AUTO_REQUIRE(qid_item_lhs, *qid_list_lhs->items.begin());
    AUTO_REQUIRE(qid_item_rhs, *qid_list_rhs->items.begin());
    BOOST_CHECK(qid_item_lhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(qid_item_rhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(qid_item_lhs->identifier == "a");
    BOOST_CHECK(qid_item_rhs->identifier == "b");

    AUTO_REQUIRE(if_block, if_stmt->statement_list);
    BOOST_REQUIRE(if_block->size() == 1);
    AUTO_REQUIRE(strlit_stmt, dynamic_pointer_cast<expression_statement>(*if_block->begin()));
    AUTO_REQUIRE(strlit, strlit_stmt->expression);
    EXPR_TO_PRIMARY(strlit);
    BOOST_CHECK(primary_strlit->type == primary_expression_type::STRING_LIT);
    BOOST_CHECK(primary_strlit->string_lit == "'fun'");

    BOOST_REQUIRE(if_stmt->elseif_list->size() == 1);
    AUTO_REQUIRE(elseif_stmt, (*if_stmt->elseif_list->begin()));
    AUTO_REQUIRE(elseif_cond, dynamic_pointer_cast<expression>(elseif_stmt->condition));
    BOOST_REQUIRE(elseif_cond->op != expression_op::NONE);
    BOOST_CHECK(elseif_cond->op == expression_op::GT_OP);
    AUTO_REQUIRE(elseif_lhs, elseif_cond->lhs);
    AUTO_REQUIRE(elseif_rhs, elseif_cond->rhs);
    EXPR_TO_PRIMARY(elseif_lhs);
    EXPR_TO_PRIMARY(elseif_rhs);
    BOOST_CHECK(primary_elseif_lhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_elseif_rhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_elseif_lhs->transposes.size() == 0);
    BOOST_CHECK(primary_elseif_rhs->transposes.size() == 0);
    AUTO_REQUIRE(elseif_qid_list_lhs, primary_elseif_lhs->qualified_id);
    AUTO_REQUIRE(elseif_qid_list_rhs, primary_elseif_rhs->qualified_id);
    AUTO_REQUIRE(elseif_qid_item_lhs, *elseif_qid_list_lhs->items.begin());
    AUTO_REQUIRE(elseif_qid_item_rhs, *elseif_qid_list_rhs->items.begin());
    BOOST_CHECK(elseif_qid_item_lhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(elseif_qid_item_rhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(elseif_qid_item_lhs->identifier == "c");
    BOOST_CHECK(elseif_qid_item_rhs->identifier == "d");
}

BOOST_AUTO_TEST_CASE(test_else_statement)
{
    matlab2r_driver the_driver;
    // Basic IF with ELSE statement
    BOOST_REQUIRE(the_driver.parse_string(
        string(
        "if a == b \n"
        "   'fun'\n"
        "else\n"
        "   'not fun'\n"
        "end"), 
        "test"
    ));

    auto ast = the_driver.ast;
    BOOST_REQUIRE(ast->size() == 1);
    AUTO_REQUIRE(if_stmt, dynamic_pointer_cast<if_statement>(*ast->begin()));
    BOOST_CHECK(if_stmt->elseif_list->size() == 0);
    AUTO_REQUIRE(cond, dynamic_pointer_cast<expression>(if_stmt->condition));
    BOOST_REQUIRE(cond->op != expression_op::NONE);
    BOOST_CHECK(cond->op == expression_op::EQ_OP);
    AUTO_REQUIRE(lhs, cond->lhs);
    AUTO_REQUIRE(rhs, cond->rhs);
    EXPR_TO_PRIMARY(lhs);
    EXPR_TO_PRIMARY(rhs);
    BOOST_CHECK(primary_lhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_rhs->u_op == unary_op::NONE);
    BOOST_CHECK(primary_lhs->transposes.size() == 0);
    BOOST_CHECK(primary_rhs->transposes.size() == 0);
    AUTO_REQUIRE(qid_list_lhs, primary_lhs->qualified_id);
    AUTO_REQUIRE(qid_list_rhs, primary_rhs->qualified_id);
    AUTO_REQUIRE(qid_item_lhs, *qid_list_lhs->items.begin());
    AUTO_REQUIRE(qid_item_rhs, *qid_list_rhs->items.begin());
    BOOST_CHECK(qid_item_lhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(qid_item_rhs->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(qid_item_lhs->identifier == "a");
    BOOST_CHECK(qid_item_rhs->identifier == "b");

    AUTO_REQUIRE(if_block, if_stmt->statement_list);
    BOOST_REQUIRE(if_block->size() == 1);
    AUTO_REQUIRE(strlit_stmt, dynamic_pointer_cast<expression_statement>(*if_block->begin()));
    AUTO_REQUIRE(strlit, strlit_stmt->expression);
    EXPR_TO_PRIMARY(strlit);
    BOOST_CHECK(primary_strlit->type == primary_expression_type::STRING_LIT);
    BOOST_CHECK(primary_strlit->string_lit == "'fun'");

    AUTO_REQUIRE(else_stmt, if_stmt->else_statement);
    AUTO_REQUIRE(else_stmt_list, else_stmt->statement_list);
    BOOST_REQUIRE(else_stmt_list->size() == 1);
    AUTO_REQUIRE(strlit2_expr, dynamic_pointer_cast<expression_statement>(*else_stmt_list->begin()));
    AUTO_REQUIRE(strlit2, strlit2_expr->expression);
    EXPR_TO_PRIMARY(strlit2);
    BOOST_CHECK(primary_strlit2->type == primary_expression_type::STRING_LIT);
    BOOST_CHECK(primary_strlit2->string_lit == "'not fun'");
}

BOOST_AUTO_TEST_CASE(test_switch_statement)
{
    matlab2r_driver the_driver;
    // basic switch statement
    BOOST_REQUIRE(the_driver.parse_string(
        string(
        "switch a\n"
        "   case 1\n"
        "       'case 1'\n"
        "   case 2\n"
        "       'case 2'\n"
        "end"
        ),
        "test"
    ));
    auto ast = the_driver.ast;
    BOOST_REQUIRE(ast->size() == 1);
    AUTO_REQUIRE(switch_stmt, dynamic_pointer_cast<switch_statement>(*ast->begin()));
    AUTO_REQUIRE(switch_expr, switch_stmt->expression);
    EXPR_TO_PRIMARY(switch_expr);
    BOOST_REQUIRE(primary_switch_expr->type == primary_expression_type::QUALIFIED_ID);
    AUTO_REQUIRE(qid_switch_expr, primary_switch_expr->qualified_id);
    BOOST_REQUIRE(qid_switch_expr->items.size() == 1);
    AUTO_REQUIRE(qid_item_switch_expr, qid_switch_expr->items[0]);
    BOOST_REQUIRE(qid_item_switch_expr->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(qid_item_switch_expr->identifier == "a");
    
    AUTO_REQUIRE(case_list, switch_stmt->case_list);
    BOOST_REQUIRE(case_list->items.size() == 2);
    AUTO_REQUIRE(case1, case_list->items[0]);
    AUTO_REQUIRE(case1_cond, case1->condition);
    EXPR_TO_PRIMARY(case1_cond);
    BOOST_REQUIRE(primary_case1_cond->type == primary_expression_type::CONSTANT);
    BOOST_CHECK(primary_case1_cond->constant == 1);
    BOOST_REQUIRE(case1->statement_list->size() == 1);
    AUTO_REQUIRE(case1_item, dynamic_pointer_cast<expression_statement>(*case1->statement_list->begin()));
    AUTO_REQUIRE(case1_expr, case1_item->expression);
    EXPR_TO_PRIMARY(case1_expr);
    BOOST_REQUIRE(primary_case1_expr->type == primary_expression_type::STRING_LIT);
    BOOST_REQUIRE(primary_case1_expr->string_lit == "'case 1'");
    
    AUTO_REQUIRE(case2, case_list->items[1]);
    AUTO_REQUIRE(case2_cond, case2->condition);
    EXPR_TO_PRIMARY(case2_cond);
    BOOST_REQUIRE(primary_case2_cond->type == primary_expression_type::CONSTANT);
    BOOST_CHECK(primary_case2_cond->constant == 2);
    BOOST_REQUIRE(case2->statement_list->size() == 1);
    AUTO_REQUIRE(case2_item, dynamic_pointer_cast<expression_statement>(*case2->statement_list->begin()));
    AUTO_REQUIRE(case2_expr, case2_item->expression);
    EXPR_TO_PRIMARY(case2_expr);
    BOOST_REQUIRE(primary_case2_expr->type == primary_expression_type::STRING_LIT);
    BOOST_REQUIRE(primary_case2_expr->string_lit == "'case 2'");
}

BOOST_AUTO_TEST_CASE(test_otherwise_statement)
{
    matlab2r_driver the_driver;
    // basic switch statement with otherwise
    BOOST_REQUIRE(the_driver.parse_string(
        string(
        "switch a\n"
        "   case 1\n"
        "       'case 1'\n"
        "   case 2\n"
        "       'case 2'\n"
        "   otherwise\n"
        "       'otherwise clause'\n"
        "end"
        ),
        "test"
    ));
    auto ast = the_driver.ast;
    BOOST_REQUIRE(ast->size() == 1);
    AUTO_REQUIRE(switch_stmt, dynamic_pointer_cast<switch_statement>(*ast->begin()));
    AUTO_REQUIRE(switch_expr, switch_stmt->expression);
    EXPR_TO_PRIMARY(switch_expr);
    BOOST_REQUIRE(primary_switch_expr->type == primary_expression_type::QUALIFIED_ID);
    AUTO_REQUIRE(qid_switch_expr, primary_switch_expr->qualified_id);
    BOOST_REQUIRE(qid_switch_expr->items.size() == 1);
    AUTO_REQUIRE(qid_item_switch_expr, qid_switch_expr->items[0]);
    BOOST_REQUIRE(qid_item_switch_expr->type == qualified_id_item_type::IDENTIFIER);
    BOOST_CHECK(qid_item_switch_expr->identifier == "a");
    
    AUTO_REQUIRE(case_list, switch_stmt->case_list);
    BOOST_REQUIRE(case_list->items.size() == 2);
    AUTO_REQUIRE(case1, case_list->items[0]);
    AUTO_REQUIRE(case1_cond, case1->condition);
    EXPR_TO_PRIMARY(case1_cond);
    BOOST_REQUIRE(primary_case1_cond->type == primary_expression_type::CONSTANT);
    BOOST_CHECK(primary_case1_cond->constant == 1);
    BOOST_REQUIRE(case1->statement_list->size() == 1);
    AUTO_REQUIRE(case1_item, dynamic_pointer_cast<expression_statement>(*case1->statement_list->begin()));
    AUTO_REQUIRE(case1_expr, case1_item->expression);
    EXPR_TO_PRIMARY(case1_expr);
    BOOST_REQUIRE(primary_case1_expr->type == primary_expression_type::STRING_LIT);
    BOOST_REQUIRE(primary_case1_expr->string_lit == "'case 1'");
    
    AUTO_REQUIRE(case2, case_list->items[1]);
    AUTO_REQUIRE(case2_cond, case2->condition);
    EXPR_TO_PRIMARY(case2_cond);
    BOOST_REQUIRE(primary_case2_cond->type == primary_expression_type::CONSTANT);
    BOOST_CHECK(primary_case2_cond->constant == 2);
    BOOST_REQUIRE(case2->statement_list->size() == 1);
    AUTO_REQUIRE(case2_item, dynamic_pointer_cast<expression_statement>(*case2->statement_list->begin()));
    AUTO_REQUIRE(case2_expr, case2_item->expression);
    EXPR_TO_PRIMARY(case2_expr);
    BOOST_REQUIRE(primary_case2_expr->type == primary_expression_type::STRING_LIT);
    BOOST_REQUIRE(primary_case2_expr->string_lit == "'case 2'");
    
    AUTO_REQUIRE(otherwise, switch_stmt->otherwise_statement);
    BOOST_REQUIRE(otherwise->statement_list->size() == 1);
    AUTO_REQUIRE(ow_item, dynamic_pointer_cast<expression_statement>(*otherwise->statement_list->begin()));
    AUTO_REQUIRE(ow_expr, ow_item->expression);
    EXPR_TO_PRIMARY(ow_expr);
    BOOST_REQUIRE(primary_ow_expr->type == primary_expression_type::STRING_LIT);
    BOOST_CHECK(primary_ow_expr->string_lit == "'otherwise clause'");
}

BOOST_AUTO_TEST_CASE(test_for_statement)
{

}

BOOST_AUTO_TEST_CASE(test_while_statement)
{

}

BOOST_AUTO_TEST_CASE(test_jump_statement)
{

}

BOOST_AUTO_TEST_CASE(test_try_catch_statement)
{

}

BOOST_AUTO_TEST_CASE(test_catch_statement)
{

}

BOOST_AUTO_TEST_CASE(test_naked_funcall_statement)
{

}

BOOST_AUTO_TEST_CASE(test_qualified_id)
{

}

BOOST_AUTO_TEST_CASE(test_expression)
{

}

BOOST_AUTO_TEST_CASE(test_primary_expression)
{

}

BOOST_AUTO_TEST_CASE(test_array_col_list)
{

}

BOOST_AUTO_TEST_CASE(test_array_row_list)
{

}

BOOST_AUTO_TEST_CASE(test_index_expression)
{

}

BOOST_AUTO_TEST_CASE(test_index_expression_list)
{

}

BOOST_AUTO_TEST_CASE(test_array_index_list)
{

}

BOOST_AUTO_TEST_CASE(test_array_index)
{

}

BOOST_AUTO_TEST_CASE(test_array_or_funcall)
{

}

BOOST_AUTO_TEST_CASE(test_array_cell)
{

}
