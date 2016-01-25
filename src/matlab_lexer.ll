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
%}

D           [0-9]
L           [a-zA-Z_]
E           [DdEe][+-]?{D}+

identifier  {L}({L}|{D})*
num         {D}+
comment     %.*{newline}
newline     \n+
ws          [\t ]

dot         \.
continue    \.\.\.

%special transpose
%%
{comment}      { loc.lines(1); }
{continue}.*$  { loc.lines(1); return yy::matlab_parser::make_CONTINUATION(loc); }

break                   return yy::matlab_parser::make_BREAK(loc);
case                    return yy::matlab_parser::make_CASE(loc);
catch                   return yy::matlab_parser::make_CATCH(loc);
clear                   return yy::matlab_parser::make_CLEAR(loc);
continue                return yy::matlab_parser::make_CONTINUE(loc);
else                    return yy::matlab_parser::make_ELSE(loc);
end                     return yy::matlab_parser::make_END(loc);
elseif                  return yy::matlab_parser::make_ELSEIF(loc);
for                     return yy::matlab_parser::make_FOR(loc);
function                return yy::matlab_parser::make_FUNCTION(loc);
global                  return yy::matlab_parser::make_GLOBAL(loc);
if                      return yy::matlab_parser::make_IF(loc);
otherwise               return yy::matlab_parser::make_OTHERWISE(loc);
persistent              return yy::matlab_parser::make_PERSISTENT(loc);
return                  return yy::matlab_parser::make_RETURN(loc);
switch                  return yy::matlab_parser::make_SWITCH(loc);
try                     return yy::matlab_parser::make_TRY(loc);
while                   return yy::matlab_parser::make_WHILE(loc);

{identifier}            { BEGIN transpose; return yy::matlab_parser::make_IDENTIFIER(yytext, loc); }
{D}+({E})?              { BEGIN transpose; return yy::matlab_parser::make_CONSTANT(yytext, loc); }
{D}*{dot}{D}+({E})?     { BEGIN transpose; return yy::matlab_parser::make_CONSTANT(yytext, loc); }
{D}+{dot}{D}*({E})?     { BEGIN transpose; return yy::matlab_parser::make_CONSTANT(yytext, loc); }

'[^\n]*'                return yy::matlab_parser::make_STRING_LITERAL(yytext, loc);

<transpose>'            return yy::matlab_parser::make_TRANSPOSE(loc);
<transpose>[^']         BEGIN 0;

".*"                    return yy::matlab_parser::make_AMUL(loc);
".^"                    return yy::matlab_parser::make_APOW(loc);
"./"                    return yy::matlab_parser::make_ADIV(loc);
".\\"                   return yy::matlab_parser::make_ARDIV(loc);
".'"                    { BEGIN transpose; return yy::matlab_parser::make_TRANSPOSE(loc); }
"<="                    return yy::matlab_parser::make_LE_OP(loc);
">="                    return yy::matlab_parser::make_GE_OP(loc);
"=="                    return yy::matlab_parser::make_EQ_OP(loc);
"~="                    return yy::matlab_parser::make_NE_OP(loc);
"("                     return yy::matlab_parser::make_LPAREN(loc);
")"                     { BEGIN transpose; return yy::matlab_parser::make_RPAREN(loc); }
"["                     return yy::matlab_parser::make_LBRACKET(loc);
"]"                     { BEGIN transpose; return yy::matlab_parser::make_RBRACKET(loc); }
"&"                     return yy::matlab_parser::make_AMP(loc);
"-"                     return yy::matlab_parser::make_MINUS(loc);
"+"                     return yy::matlab_parser::make_PLUS(loc);
"*"                     return yy::matlab_parser::make_TIMES(loc);
"/"                     return yy::matlab_parser::make_FSLASH(loc);
"\\"                    return yy::matlab_parser::make_BSLASH(loc);
"<"                     return yy::matlab_parser::make_LT_OP(loc);
">"                     return yy::matlab_parser::make_GT_OP(loc);
"|"                     return yy::matlab_parser::make_VBAR(loc);
{ws}                    loc.step();

%{
    loc.step();
%}

{comment}       loc.lines(1);
{newline}       {
    loc.lines(yyleng);
    loc.step();
    /* return yy::imparser::make_NEWLINE(loc); */
}
{ws}            loc.step();

%%

int yyFlexLexer::yylex()
{
    assert(false && "yyFlexLexer::yylex() called; this should not happen");
    return 0;
}

