#include "matlab2r_driver.hpp"
#include "ast.hpp"
#include <string>
#define BOOST_TEST_MODULE test_parser
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(test_if_statement)
{
    matlab2r_driver the_driver;
    BOOST_REQUIRE(the_driver.parse_string(
        string("if a == b \n"
        "   'fun'\n"
        "end"), 
        "test"
    ));
    
}