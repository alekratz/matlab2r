%skeleton "lalr1.cc"
%require "3.0.4"
%defines
%locations

%define parser_class_name {matlab_parser}
%define api.value.type variant
%define api.token.constructor
%define parse.assert
%define parse.trace
%define parse.error verbose
%define api.token.prefix {TOK_}

%code requires
{
    #include <string>
    #include <vector>
    #include <cstdint>
    #include "ast.hpp"
    class matlab2r_driver;
}

%code
{
    #include "matlab2r_driver.hpp"
    #include "matlab_lexer.hpp"
    #include <sstream>
    #undef yylex
    #define yylex driver.lexer->lex
}

%param { matlab2r_driver& driver }
%printer { yyoutput << $$; } <*>;

%initial-action
{
    // Initialize the initial location
    @$.begin.filename = @$.end.filename = &driver.streamname;
}

// Tokens
%token
    END     0       "end of file"
    NEWLINE 10      "newline"
    BREAK
    CASE
    CATCH
    CLEAR
    CONTINUE
    ELSE
    END_KEYW
    ELSEIF
    FOR
    FUNCTION
    GLOBAL
    IF
    OTHERWISE
    PERSISTENT
    RETURN
    SWITCH
    TRY
    WHILE
    AMUL
    APOW
    ADIV
    ARDIV
    TRANSPOSE
    NCTRANSPOSE
    LE_OP
    GE_OP
    EQ_OP
    NE_OP
    TILDE
    SEMICOLON
    COMMA
    COLON
    EQUALS
    LPAREN
    RPAREN
    LBRACKET
    RBRACKET
    LBRACE
    RBRACE
    AMP
    MINUS
    PLUS
    TIMES
    FSLASH
    BSLASH
    LT_OP
    GT_OP
    POW
    VBAR
    DOT

%token <std::string>        IDENTIFIER
%token <std::string>        CONSTANT
%token <std::string>        STRING_LITERAL
%token <std::string>        NAKED_ARG

%type <ast::function_declare_p>         function_declare
%type <ast::identifier_list_p>          function_return_list
%type <ast::identifier_list_p>          function_args
%type <ast::identifier_list_p>          function_ident_list
%type <ast::statement_list_p>           statement_list
%type <ast::statement_p>                statement
%type <ast::global_statement_p>         global_statement
%type <ast::clear_statement_p>          clear_statement
%type <ast::identifier_list_p>          identifier_list
%type <ast::expression_statement_p>     expression_statement
%type <ast::assignment_statement_p>     assignment_statement
%type <ast::statement_p>                selection_statement
%type <ast::if_statement_p>             if_statement
%type <ast::elseif_list_p>              elseif_list
%type <ast::elseif_statement_p>         elseif_statement
%type <ast::else_statement_p>           else_statement
%type <ast::switch_statement_p>         switch_statement
%type <ast::case_list_p>                case_list
%type <ast::case_statement_p>           case_statement
%type <ast::otherwise_statement_p>      otherwise_statement
%type <ast::block_statement_p>          iteration_statement
%type <ast::for_statement_p>            for_statement
%type <ast::while_statement_p>          while_statement
%type <ast::jump_statement_p>           jump_statement
%type <ast::try_statement_p>            try_catch_statement
%type <ast::catch_statement_p>          catch_statement
%type <ast::naked_funcall_statement_p>  naked_funcall_statement
%type <ast::identifier_list_p>          naked_arg_list

%type <ast::qualified_id_p>             qualified_id
%type <ast::qualified_id_item_p>        qualified_id_item
%type <ast::assignment_expression_p>    assignment_expression
%type <ast::expression_p>               expression
%type <ast::unary_expression_p>         unary_expression
%type <ast::postfix_expression_p>       postfix_expression
%type <ast::primary_expression_p>       primary_expression
%type <ast::array_col_list_p>           array_col_list
%type <ast::array_row_list_p>           array_row_list
%type <ast::index_expression_p>         index_expression
%type <ast::index_expression_list_p>    index_expression_list
%type <ast::index_expression_list_p>    array_or_funcall_tail
%type <ast::index_expression_list_p>    array_cell_tail

%left COLON
%left VBAR
%left AMP
%left GT_OP GE_OP LT_OP LE_OP EQ_OP NE_OP
%left PLUS MINUS
%left TIMES FSLASH BSLASH POW AMUL ADIV ARDIV APOW

%%

%start unit;

unit    : statement_list { driver.ast = $1; }

eostmt  : COMMA
        | SEMICOLON
        | NEWLINE
        ;

eostmt_or_eof
        : eostmt
        | END
        ;

/******************************************************************************
 * Function decls
 *****************************************************************************/

function_declare
        : FUNCTION IDENTIFIER function_args eostmt statement_list optional_end eostmt_or_eof
            { $$ = std::make_shared<ast::function_declare>($2, $3, $5); }
        | FUNCTION function_return_list EQUALS IDENTIFIER function_args eostmt statement_list optional_end eostmt_or_eof
            { $$ = std::make_shared<ast::function_declare>($2, $4, $5, $7); }
        ;

optional_end
        : END_KEYW
        | %empty
        ;

function_return_list
        : IDENTIFIER { $$ = std::make_shared<ast::identifier_list>($1); }
        | LBRACKET function_ident_list RBRACKET { $$ = $2; }
        ;

function_args
        : LPAREN function_ident_list RPAREN { $$ = $2; }
        | %empty { $$ = std::make_shared<ast::identifier_list>(); }
        ;

function_ident_list
        : IDENTIFIER { $$ = std::make_shared<ast::identifier_list>($1); }
        | IDENTIFIER COMMA function_ident_list 
        {
            $3->add_front($1);
            $$ = $3;
        }
        | %empty
            { $$ = std::make_shared<ast::identifier_list>(); }
        ;

/******************************************************************************
 * Statements
 *****************************************************************************/

statement_list
        : statement statement_list
        {
            if($1 != nullptr)
                $2->add_front($1);
            $$ = $2;
        }
        | function_declare statement_list 
        {
            $2->add_front($1);
            $$ = $2;
        }
        | %empty 
            { $$ = std::make_shared<ast::statement_list>(); }
        | error { yyerrok; }
        ;

statement
        : global_statement 
            { $$ = $1; }
        | clear_statement 
            { $$ = $1; }
        | expression_statement 
            { $$ = $1; }
        | assignment_statement 
            { $$ = $1; }
        | selection_statement 
            { $$ = $1; }
        | iteration_statement 
            { $$ = $1; }
        | jump_statement 
            { $$ = $1; }
        | try_catch_statement 
            { $$ = $1; }
        | naked_funcall_statement 
            { $$ = $1; }
        | eostmt 
            { $$ = nullptr; }
        ;

global_statement
        : GLOBAL identifier_list eostmt_or_eof
            { $$ = std::make_shared<ast::global_statement>($2); }
        ;

clear_statement
        : CLEAR identifier_list eostmt_or_eof 
            { $$ = std::make_shared<ast::clear_statement>($2); }
        | CLEAR eostmt_or_eof 
            { $$ = std::make_shared<ast::clear_statement>(); }
        ;

identifier_list
        : IDENTIFIER
            { $$ = std::make_shared<ast::identifier_list>($1); }
        | identifier_list IDENTIFIER
        {
            $1->add_front($2);
            $$ = $1;
        }
        ;

expression_statement
        : expression eostmt_or_eof
            { $$ = std::make_shared<ast::expression_statement>($1); }
        ;

assignment_statement
        : assignment_expression eostmt_or_eof
            { $$ = std::make_shared<ast::assignment_statement>($1); }
        ;

selection_statement
        : if_statement 
            { $$ = $1; }
        | switch_statement
            { $$ = $1; }
        ;

if_statement
        : IF expression statement_list elseif_list else_statement END_KEYW eostmt_or_eof
            { $$ = std::make_shared<ast::if_statement>($2, $3, $4, $5); }
        ;

elseif_list
        : elseif_statement elseif_list
            { 
                $2->add_front($1);
                $$ = $2;
            }
        | %empty 
            { $$ = std::make_shared<ast::elseif_list>(); }
        ;

elseif_statement
        : ELSEIF expression statement_list
            { $$ = std::make_shared<ast::elseif_statement>($2, $3); }
        ;

else_statement
        : ELSE statement_list
            { $$ = std::make_shared<ast::else_statement>($2); }
        | %empty
            { $$ = nullptr; }
        ;

switch_statement
        : SWITCH expression eostmt case_list otherwise_statement END_KEYW eostmt_or_eof
            { $$ = std::make_shared<ast::switch_statement>($2, $4, $5); }
        ;

case_list
        : case_statement case_list
        {
            if($1 != nullptr)
                $2->add_front($1);
            $$ = $2;
        }
        | %empty
            { $$ = std::make_shared<ast::case_list>(); }
        ;

case_statement
        : CASE expression eostmt statement_list
            { $$ = std::make_shared<ast::case_statement>($2, $4); }
        | eostmt
            { $$ = nullptr; }
        ;

otherwise_statement
        : OTHERWISE eostmt statement_list
            { $$ = std::make_shared<ast::otherwise_statement>($3); }
        | %empty
            { $$ = nullptr; }
        ;

iteration_statement
        : while_statement
            { $$ = $1; }
        | for_statement
            { $$ = $1; }
        ;

while_statement
        : WHILE expression statement_list END_KEYW eostmt_or_eof
            { $$ = std::make_shared<ast::while_statement>($2, $3); }
        ;

for_statement
        : FOR IDENTIFIER EQUALS expression statement_list END_KEYW eostmt_or_eof
            { $$ = std::make_shared<ast::for_statement>($2, $4, $5); }
        | FOR LPAREN IDENTIFIER EQUALS expression RPAREN statement_list END_KEYW eostmt_or_eof
            { $$ = std::make_shared<ast::for_statement>($3, $5, $7); }
        ;

jump_statement
        : BREAK eostmt
            { $$ = std::make_shared<ast::jump_statement>(ast::jump_statement_type::BREAK); }
        | CONTINUE eostmt
            { $$ = std::make_shared<ast::jump_statement>(ast::jump_statement_type::CONTINUE); }
        | RETURN eostmt
            { $$ = std::make_shared<ast::jump_statement>(ast::jump_statement_type::RETURN); }
        ;

try_catch_statement
        : TRY statement_list catch_statement END_KEYW eostmt_or_eof
            { $$ = std::make_shared<ast::try_statement>($2, $3); }
        | TRY statement_list END_KEYW eostmt_or_eof
            { $$ = std::make_shared<ast::try_statement>($2, nullptr); }
        ;

catch_statement
        : CATCH IDENTIFIER statement_list
            { $$ = std::make_shared<ast::catch_statement>($2, $3); }
        | CATCH statement_list
            { $$ = std::make_shared<ast::catch_statement>($2); }
        ;

naked_funcall_statement
        : IDENTIFIER IDENTIFIER { driver.lexer->begin_naked_args(); } naked_arg_list eostmt_or_eof 
            { $$ = std::make_shared<ast::naked_funcall_statement>($1, $2, $4); }
        | IDENTIFIER eostmt_or_eof
            { $$ = std::make_shared<ast::naked_funcall_statement>($1); }
        ;
        
naked_arg_list
        : NAKED_ARG naked_arg_list
        {
            $2->add_front($1);
            $$ = $2;
        }
        | %empty
            { $$ = std::make_shared<ast::identifier_list>(); }
        ;

/******************************************************************************
 * Expressions
 *****************************************************************************/

assignment_expression
        : postfix_expression EQUALS expression { $$ = std::make_shared<ast::assignment_expression>($1, $3); }
        ;

postfix_expression
        : primary_expression { $$ = std::make_shared<ast::postfix_expression>($1); }
        | postfix_expression TRANSPOSE
        { 
            $1->add_front(ast::postfix_op::TRANSPOSE);
            $$ = $1;
        }
        | postfix_expression NCTRANSPOSE
        { 
            $1->add_front(ast::postfix_op::NCTRANSPOSE);
            $$ = $1;
        }
        ;

primary_expression
        : qualified_id
            { $$ = std::make_shared<ast::primary_expression>($1); }
        | STRING_LITERAL
            { $$ = std::make_shared<ast::primary_expression>($1); }
        | CONSTANT
            { $$ = std::make_shared<ast::primary_expression>($1); }
        | LBRACKET array_col_list RBRACKET
            { $$ = std::make_shared<ast::primary_expression>($2, ast::primary_expression_type::MATRIX); }
        | LBRACE array_col_list RBRACE
            { $$ = std::make_shared<ast::primary_expression>($2, ast::primary_expression_type::CELL_ARRAY); }
        | LPAREN expression RPAREN
            { $$ = std::make_shared<ast::primary_expression>($2); }
        ;

expression
        : unary_expression { $$ = std::make_shared<ast::expression>($1); }
        | unary_expression COLON expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::COLON, $1); }
        | unary_expression VBAR expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::VBAR, $1); }
        | unary_expression AMP expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::AMP, $1); }
        | unary_expression EQ_OP expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::EQ_OP, $1); }
        | unary_expression NE_OP expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::NE_OP, $1); }
        | unary_expression LT_OP expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::LT_OP, $1); }
        | unary_expression GT_OP expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::GT_OP, $1); }
        | unary_expression LE_OP expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::LE_OP, $1); }
        | unary_expression GE_OP expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::GE_OP, $1); }
        | unary_expression PLUS expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::PLUS, $1); }
        | unary_expression MINUS expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::MINUS, $1); }
        | unary_expression TIMES expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::TIMES, $1); }
        | unary_expression FSLASH expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::FSLASH, $1); }
        | unary_expression BSLASH expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::BSLASH, $1); }
        | unary_expression POW expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::POW, $1); }
        | unary_expression AMUL expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::AMUL, $1); }
        | unary_expression ADIV expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::ADIV, $1); }
        | unary_expression ARDIV expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::ARDIV, $1); }
        | unary_expression APOW expression
            { $$ = std::make_shared<ast::expression>($3, ast::expression_op::APOW, $1); }
        ;

unary_expression
        : PLUS postfix_expression
            { $$ = std::make_shared<ast::unary_expression>(ast::unary_op::PLUS, $2); }
        | MINUS postfix_expression
            { $$ = std::make_shared<ast::unary_expression>(ast::unary_op::MINUS, $2); }
        | TILDE postfix_expression
            { $$ = std::make_shared<ast::unary_expression>(ast::unary_op::TILDE, $2); }
        | postfix_expression 
            { $$ = std::make_shared<ast::unary_expression>($1); }
        ;

array_or_funcall_tail
        : LPAREN index_expression_list RPAREN
            { $$ = $2; }
        ;

array_cell_tail
        : LBRACE index_expression_list RBRACE
            { $$ = $2; }
        ;

index_expression_list
        : index_expression
        {
            $$ = std::make_shared<ast::index_expression_list>();
            $$->add_front($1);
        }
        | index_expression COMMA index_expression_list
        {
            $3->add_front($1);
            $$ = $3;
        }
        | %empty
            { $$ = std::make_shared<ast::index_expression_list>(); }
        ;

index_expression
        : COLON
            { $$ = std::make_shared<ast::index_expression>(); }
        | expression
            { $$ = std::make_shared<ast::index_expression>($1); }
        ;

qualified_id
        : qualified_id_item
            { $$ = std::make_shared<ast::qualified_id>($1); }
        | qualified_id_item DOT qualified_id
        {
            $3->add_front($1);
            $$ = $3;
        }
        ;

qualified_id_item
        : IDENTIFIER 
        { 
            $$ = std::make_shared<ast::qualified_id_item>();
            $$->identifier = $1;
        }
        | LPAREN expression RPAREN // apparently this is allowed
        {
            $$ = std::make_shared<ast::qualified_id_item>();
            $$->expression = $2;
        }
        | qualified_id_item array_or_funcall_tail
        {
            $1->array_or_funcall_tail = $2;
            $$ = $1;
        }
        | qualified_id_item array_cell_tail { }
        {
            $1->array_cell_tail = $2;
            $$ = $1;
        }
        ;

/******************************************************************************
 * Array indexing
 *****************************************************************************/

array_row_list
        : expression
        {
            $$ = std::make_shared<ast::array_row_list>();
            $$->add_front($1);
        }
        | expression array_row_list
        {
            $2->add_front($1);
            $$ = $2;
        }
        | expression COMMA array_row_list
        {
            $3->add_front($1);
            $$ = $3;
        }
        | NEWLINE array_row_list
            { $$ = $2; }
        | %empty
            { $$ = std::make_shared<ast::array_row_list>(); }
        ;

array_col_list
        : array_row_list 
        {
            $$ = std::make_shared<ast::array_col_list>();
            // Push the row to the list of rows if it has any items; otherwise, it is empty.
            if($1->items.size() != 0) $$->add_front($1);
        }
        | array_row_list SEMICOLON array_col_list
        {
            if($1 != nullptr) $3->add_front($1);
            $$ = $3;
        }
        | NEWLINE array_col_list
            { $$ = $2; }
        ;

%%

void yy::matlab_parser::error(const location_type& l, const std::string& m)
{
    driver.error(l, m);
}