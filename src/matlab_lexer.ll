%option c++ noyywrap nounput batch debug noinput

%{
#include "matlab2r_driver.hpp"
#include "matlab_lexer.hpp"
#include "parser.hpp"

#include <sstream>
#include <string>
#include <cstdint>

#define YY_USER_ACTION loc.columns(yyleng);

#undef yywrap
#define yywrap() 1
// HACK : remove this really hacky paren depth tracker and find a better way to ignore special keywords
static int32_t paren_depth = 0;
%}

D           [0-9]
L           [a-zA-Z_]
E           [DdEe][+-]?{D}+

identifier  {L}({L}|{D})*
num         {D}+
comment     %[^\n]*{newline}
newline     \n+
ws          [\t ]

dot         \.
continue    \.\.\.
fcall {identifier}[ \t]{ws}*[^(]

%special transpose string_lit naked_args

%%
{comment}               { unput('\n'); }
{continue}.*\n          { loc.lines(1); }

break                   { BEGIN string_lit; return yy::matlab_parser::make_BREAK(loc); }
case                    { BEGIN string_lit; return yy::matlab_parser::make_CASE(loc); }
catch                   { BEGIN string_lit; return yy::matlab_parser::make_CATCH(loc); }
clear                   { BEGIN string_lit; return yy::matlab_parser::make_CLEAR(loc); }
continue                { BEGIN string_lit; return yy::matlab_parser::make_CONTINUE(loc); }
else                    { BEGIN string_lit; return yy::matlab_parser::make_ELSE(loc); }
end                     { 
                            // we could catch mismatched parens, buuuuut that's none of my business
                            if(paren_depth > 0)
                            {
                                BEGIN transpose;
                                return yy::matlab_parser::make_IDENTIFIER(yytext, loc);
                            }
                            else
                            {
                                BEGIN string_lit;
                                return yy::matlab_parser::make_END_KEYW(loc);
                            }
                        }
elseif                  { BEGIN string_lit; return yy::matlab_parser::make_ELSEIF(loc); }
for                     { BEGIN string_lit; return yy::matlab_parser::make_FOR(loc); }
function                { BEGIN string_lit; return yy::matlab_parser::make_FUNCTION(loc); }
global                  { BEGIN string_lit; return yy::matlab_parser::make_GLOBAL(loc); }
if                      { BEGIN string_lit; return yy::matlab_parser::make_IF(loc); }
otherwise               { BEGIN string_lit; return yy::matlab_parser::make_OTHERWISE(loc); }
persistent              { BEGIN string_lit; return yy::matlab_parser::make_PERSISTENT(loc); }
return                  { BEGIN string_lit; return yy::matlab_parser::make_RETURN(loc); }
switch                  { BEGIN string_lit; return yy::matlab_parser::make_SWITCH(loc); }
try                     { BEGIN string_lit; return yy::matlab_parser::make_TRY(loc); }
while                   { BEGIN string_lit; return yy::matlab_parser::make_WHILE(loc); }

{identifier}            { BEGIN transpose; return yy::matlab_parser::make_IDENTIFIER(yytext, loc); }
{D}+({E})?              { BEGIN transpose; return yy::matlab_parser::make_CONSTANT(yytext, loc); }
{D}*{dot}{D}+({E})?     { BEGIN transpose; return yy::matlab_parser::make_CONSTANT(yytext, loc); }
{D}+{dot}{D}*({E})?     { BEGIN transpose; return yy::matlab_parser::make_CONSTANT(yytext, loc); }

<string_lit>'[^'\n]*'/' { BEGIN string_lit; return yy::matlab_parser::make_STRING_LITERAL(yytext, loc); }
<string_lit>'[^'\n]*'   { BEGIN string_lit; return yy::matlab_parser::make_STRING_LITERAL(yytext, loc); }
<transpose>{ws}         { BEGIN string_lit; }
<transpose>'            { BEGIN transpose; return yy::matlab_parser::make_TRANSPOSE(loc); }

<naked_args>{newline}   { BEGIN string_lit; loc.lines(1); return yy::matlab_parser::make_NEWLINE(loc); }
<naked_args>{ws}*       
<naked_args>[^\t\n ]*   { return yy::matlab_parser::make_NAKED_ARG(yytext, loc); }

".*"                    { BEGIN string_lit; return yy::matlab_parser::make_AMUL(loc); }
".^"                    { BEGIN string_lit; return yy::matlab_parser::make_APOW(loc); }
"./"                    { BEGIN string_lit; return yy::matlab_parser::make_ADIV(loc); }
".\\"                   { BEGIN string_lit; return yy::matlab_parser::make_ARDIV(loc); }
".'"                    { BEGIN transpose; return yy::matlab_parser::make_NCTRANSPOSE(loc); }
"<="                    { BEGIN string_lit; return yy::matlab_parser::make_LE_OP(loc); }
">="                    { BEGIN string_lit; return yy::matlab_parser::make_GE_OP(loc); }
"=="                    { BEGIN string_lit; return yy::matlab_parser::make_EQ_OP(loc); }
"~="                    { BEGIN string_lit; return yy::matlab_parser::make_NE_OP(loc); }
"~"                     { BEGIN string_lit; return yy::matlab_parser::make_TILDE(loc); }
";"                     { BEGIN string_lit; return yy::matlab_parser::make_SEMICOLON(loc); }
","                     { BEGIN string_lit; return yy::matlab_parser::make_COMMA(loc); }
":"                     { BEGIN string_lit; return yy::matlab_parser::make_COLON(loc); }
"="                     { BEGIN string_lit; return yy::matlab_parser::make_EQUALS(loc); }
"("                     { 
                            paren_depth++;
                            BEGIN string_lit;
                            return yy::matlab_parser::make_LPAREN(loc);
                        }
")"                     {
                            paren_depth--;
                            BEGIN transpose;
                            return yy::matlab_parser::make_RPAREN(loc);
                        }
"["                     { BEGIN string_lit; return yy::matlab_parser::make_LBRACKET(loc); }
"]"                     { BEGIN transpose; return yy::matlab_parser::make_RBRACKET(loc); }
"{"                     { 
                            paren_depth++;
                            BEGIN string_lit;
                            return yy::matlab_parser::make_LBRACE(loc);
                        }
"}"                     {
                            paren_depth--;
                            BEGIN transpose;
                            return yy::matlab_parser::make_RBRACE(loc);
                        }
"&&"                    { BEGIN string_lit; return yy::matlab_parser::make_AMP(loc); }
"||"                    { BEGIN string_lit; return yy::matlab_parser::make_VBAR(loc); }
"&"                     { BEGIN string_lit; return yy::matlab_parser::make_AMP(loc); }
"|"                     { BEGIN string_lit; return yy::matlab_parser::make_VBAR(loc); }
"-"                     { BEGIN string_lit; return yy::matlab_parser::make_MINUS(loc); }
"+"                     { BEGIN string_lit; return yy::matlab_parser::make_PLUS(loc); }
"*"                     { BEGIN string_lit; return yy::matlab_parser::make_TIMES(loc); }
"/"                     { BEGIN string_lit; return yy::matlab_parser::make_FSLASH(loc); }
"\\"                    { BEGIN string_lit; return yy::matlab_parser::make_BSLASH(loc); }
"<"                     { BEGIN string_lit; return yy::matlab_parser::make_LT_OP(loc); }
">"                     { BEGIN string_lit; return yy::matlab_parser::make_GT_OP(loc); }
"^"                     { BEGIN string_lit; return yy::matlab_parser::make_POW(loc); }
"."                     { BEGIN string_lit; return yy::matlab_parser::make_DOT(loc); }
{newline}               { BEGIN string_lit; loc.lines(yyleng); return yy::matlab_parser::make_NEWLINE(loc); }
{ws}                    

.                       {  }
%{
    loc.step();
%}

%%

int yyFlexLexer::yylex()
{
    assert(false && "yyFlexLexer::yylex() called; this should not happen");
    return 0;
}

void matlab_lexer::begin_garbage_mode()
{
    BEGIN naked_args;
}
