#include "matlab2r_driver.hpp"
#include "ast.hpp"
#include <string>
#define BOOST_TEST_MODULE test_parser
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace ast;

#define AUTO_REQUIRE(A, B) auto A = B; \
    BOOST_REQUIRE(A != nullptr)
#define EXPR_TO_PRIMARY(E) AUTO_REQUIRE(unary_ ## E, E->expr); \
        AUTO_REQUIRE(postfix_ ## E, unary_ ## E ->expr); \
        AUTO_REQUIRE(primary_ ## E, postfix_ ## E ->expr)
; // this is here to keep me from going insane

BOOST_AUTO_TEST_CASE(test_function_declare)
{

}

BOOST_AUTO_TEST_CASE(test_function_return_list)
{

}

BOOST_AUTO_TEST_CASE(test_function_args)
{

}

BOOST_AUTO_TEST_CASE(test_function_ident_list)
{

}

BOOST_AUTO_TEST_CASE(test_statement_list)
{

}

BOOST_AUTO_TEST_CASE(test_statement)
{

}

BOOST_AUTO_TEST_CASE(test_global_statement)
{

}

BOOST_AUTO_TEST_CASE(test_clear_statement)
{

}

BOOST_AUTO_TEST_CASE(test_identifier_list)
{

}

BOOST_AUTO_TEST_CASE(test_expression_statement)
{

}

BOOST_AUTO_TEST_CASE(test_assignment_statement)
{

}

BOOST_AUTO_TEST_CASE(test_selection_statement)
{

}

BOOST_AUTO_TEST_CASE(test_if_statement)
{
    matlab2r_driver the_driver;
    // Basic IF statement
    {
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
        BOOST_CHECK(unary_lhs->op == unary_op::NONE);
        BOOST_CHECK(unary_rhs->op == unary_op::NONE);
        BOOST_CHECK(postfix_lhs->transposes.size() == 0);
        BOOST_CHECK(postfix_rhs->transposes.size() == 0);
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
    // Basic IF statement with ELSE and ELSEIF
    {
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
        BOOST_CHECK(unary_lhs->op == unary_op::NONE);
        BOOST_CHECK(unary_rhs->op == unary_op::NONE);
        BOOST_CHECK(postfix_lhs->transposes.size() == 0);
        BOOST_CHECK(postfix_rhs->transposes.size() == 0);
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
        BOOST_CHECK(unary_elseif_lhs->op == unary_op::NONE);
        BOOST_CHECK(unary_elseif_rhs->op == unary_op::NONE);
        BOOST_CHECK(postfix_elseif_lhs->transposes.size() == 0);
        BOOST_CHECK(postfix_elseif_rhs->transposes.size() == 0);
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
    BOOST_CHECK(unary_lhs->op == unary_op::NONE);
    BOOST_CHECK(unary_rhs->op == unary_op::NONE);
    BOOST_CHECK(postfix_lhs->transposes.size() == 0);
    BOOST_CHECK(postfix_rhs->transposes.size() == 0);
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
    BOOST_CHECK(unary_elseif_lhs->op == unary_op::NONE);
    BOOST_CHECK(unary_elseif_rhs->op == unary_op::NONE);
    BOOST_CHECK(postfix_elseif_lhs->transposes.size() == 0);
    BOOST_CHECK(postfix_elseif_rhs->transposes.size() == 0);
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
    BOOST_CHECK(unary_lhs->op == unary_op::NONE);
    BOOST_CHECK(unary_rhs->op == unary_op::NONE);
    BOOST_CHECK(postfix_lhs->transposes.size() == 0);
    BOOST_CHECK(postfix_rhs->transposes.size() == 0);
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

}

BOOST_AUTO_TEST_CASE(test_case_list)
{

}

BOOST_AUTO_TEST_CASE(test_case_statement)
{

}

BOOST_AUTO_TEST_CASE(test_otherwise_statement)
{

}

BOOST_AUTO_TEST_CASE(test_iteration_statement)
{

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

BOOST_AUTO_TEST_CASE(test_naked_arg_list)
{

}

BOOST_AUTO_TEST_CASE(test_qualified_id)
{

}

BOOST_AUTO_TEST_CASE(test_qualified_id_item)
{

}

BOOST_AUTO_TEST_CASE(test_assignment_expression)
{

}

BOOST_AUTO_TEST_CASE(test_expression)
{

}

BOOST_AUTO_TEST_CASE(test_unary_expression)
{

}

BOOST_AUTO_TEST_CASE(test_postfix_expression)
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
