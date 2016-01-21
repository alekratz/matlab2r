#ifndef MATLAB2R_DRIVER_HPP
#define MATLAB2R_DRIVER_HPP 

#include "types.hpp"
#include "parser.hpp"
#include "matlab_lexer.hpp"
#include <string>

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
    std::string streamname;
    matlab_lexer *lexer;

    bool trace_scanning;
    bool trace_parsing;
};

#endif
