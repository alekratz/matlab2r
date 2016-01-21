#ifndef MATLAB2R_DRIVER_HPP
#define MATLAB2R_DRIVER_HPP 

#include "types.hpp"
#include "parser.hpp"
#include "matlab_lexer.hpp"
#include <string>
#include <iostream>

class matlab2r_driver
{
public:
    matlab2r_driver()
        : streamname()
        , lexer(nullptr)
        , trace_scanning(false)
        , trace_parsing(false)
    { }
    virtual ~matlab2r_driver() = default;

public:
    bool parse_stream(std::istream& in, cstref streamname, std::ostream& out = std::cout);
    bool parse_file(cstref filename, std::ostream& out = std::cout);
    void error(const yy::location& l, cstref m, cstref t);
    void error(const yy::location& l, cstref m);
    void error(cstref m);

public:
    std::string streamname;
    matlab_lexer *lexer;

    bool trace_scanning;
    bool trace_parsing;
};

#endif
