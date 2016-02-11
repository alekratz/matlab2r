cmake_minimum_required(VERSION 3.0)
# Project info
project(matlab2r)
set(matlab2r_VERSION_MAJOR 0)
set(matlab2r_VERSION_MINOR 1)

# Load modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

find_package(Boost REQUIRED COMPONENTS filesystem system)

BISON_TARGET(matlab_parser src/matlab_parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(matlab_lexer src/matlab_lexer.ll ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS "-+ --header")
ADD_FLEX_BISON_DEPENDENCY(matlab_lexer matlab_parser)

include_directories("${CMAKE_CURRENT_BINARY_DIR}" "include")

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++14")

set(IM_SOURCES 
    src/main.cpp
    src/matlab2r_driver.cpp
    src/ast/accept.cpp
    src/ast/block_statement.cpp
    src/ast/for_statement.cpp
    src/ast/while_statement.cpp
    src/ast/if_statement.cpp
    src/ast/elseif_statement.cpp
    src/ast/else_statement.cpp
    src/ast/switch_statement.cpp
    src/ast/case_statement.cpp
    src/ast/otherwise_statement.cpp
    src/ast/try_statement.cpp
    src/ast/catch_statement.cpp
    src/ast/naked_arg_list.cpp
    src/ast/expression.cpp
    src/ast/unary_expression.cpp
    src/ast/postfix_expression.cpp
    src/ast/primary_expression.cpp
    src/ast/index_expression.cpp
    src/ast/qualified_id.cpp
    src/ast/list_node.cpp
    ${FLEX_matlab_lexer_OUTPUTS} 
    ${BISON_matlab_parser_OUTPUTS})

add_executable(matlab2r ${IM_SOURCES})
target_link_libraries(matlab2r "${Boost_LIBRARIES}")
