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


L           [a-zA-Z_]
D           [0-9]
H           {D}|[a-fA-F]

identifier  {L}({L}|{D})*
num         {D}+
comment     #.*{newline}
newline     \n+
ws          [\t ]

%%

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

