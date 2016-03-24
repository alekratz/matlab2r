cmake_minimum_required(VERSION 3.0)
# Project info
project(matlab2r)
set(matlab2r_VERSION_MAJOR 0)
set(matlab2r_VERSION_MINOR 1)
set(matlab2r_VERSION_TWEAK 0)
set(matlab2r_VERSION_SUFFIX "alpha")
add_definitions(-DVERSION_STR="v${matlab2r_VERSION_MAJOR}.${matlab2r_VERSION_MINOR}.${matlab2r_VERSION_TWEAK}-${matlab2r_VERSION_SUFFIX}")

set(USE_GIT_VERSIONING true CACHE BOOL "Determines whether to use git versioning if available.")
# Git build options
find_package(Git)
if(${GIT_FOUND} AND ${USE_GIT_VERSIONING})
    add_definitions(-DWITH_GIT_INFO=1)
    # The following execute_process stolen from http://xit0.org/2013/04/cmake-use-git-branch-and-commit-details-in-project/
    # thanks, bud.
    # Get the latest abbreviated commit hash of the working branch
    execute_process(
      COMMAND git log -1 --format=%h
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE GIT_COMMIT_HASH
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    add_definitions(-DGIT_COMMIT_STR="${GIT_COMMIT_HASH}")
endif(${GIT_FOUND} AND ${USE_GIT_VERSIONING})

# Load modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

find_package(Boost REQUIRED COMPONENTS filesystem system unit_test_framework)

BISON_TARGET(matlab_parser src/matlab_parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(matlab_lexer src/matlab_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS "-+ --header")
ADD_FLEX_BISON_DEPENDENCY(matlab_lexer matlab_parser)

include_directories("${CMAKE_CURRENT_BINARY_DIR}" "include")
set(CMAKE_CXX_FLAGS "-g -Wall --std=c++14")

set(M2R_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/matlab2r_driver.cpp
    ${CMAKE_SOURCE_DIR}/src/visitor/codegen_visitor.cpp
    ${CMAKE_SOURCE_DIR}/src/visitor/function_name_visitor.cpp
    ${CMAKE_SOURCE_DIR}/src/visitor/sanity_check_visitor.cpp
    ${CMAKE_SOURCE_DIR}/src/visitor/rename_visitor.cpp

    ${CMAKE_SOURCE_DIR}/src/ast/accept.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/block_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/for_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/while_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/function_declare.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/expression_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/assignment_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/if_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/elseif_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/else_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/switch_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/case_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/otherwise_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/try_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/catch_statement.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/assignment_expression.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/expression.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/unary_expression.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/postfix_expression.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/primary_expression.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/index_expression.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/array_index.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/qualified_id.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/list_node.cpp

    ${CMAKE_SOURCE_DIR}/src/ast/generator/funcall_arg_assign.cpp
    ${FLEX_matlab_lexer_OUTPUTS} 
    ${BISON_matlab_parser_OUTPUTS})

enable_testing()
add_subdirectory(tests)

add_executable(matlab2r ${CMAKE_SOURCE_DIR}/src/main.cpp ${M2R_SOURCES})
target_link_libraries(matlab2r ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
