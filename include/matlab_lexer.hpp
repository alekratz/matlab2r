#ifndef MATLAB_LEXER_HPP
#define MATLAB_LEXER_HPP

#include "matlab2r_driver.hpp"
#include "parser.hpp"

#ifndef __FLEX_LEXER_H
#define yyFlexLexer yyFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif

#define YY_DECL \
    yy::matlab_parser::symbol_type matlab_lexer::lex(matlab2r_driver& driver)
#define yyterminate() return yy::matlab_parser::make_END(loc);

class yyFlexLexer;

class matlab_lexer
    : public yyFlexLexer
{
public:
    matlab_lexer(std::istream *in = nullptr, std::ostream *out = nullptr)
        : yyFlexLexer(in, out)
    { }

public:
    yy::matlab_parser::symbol_type lex(matlab2r_driver& driver);
    // Location of the current token
    yy::location loc;

public:
    void begin_garbage_mode();
};

#endif
