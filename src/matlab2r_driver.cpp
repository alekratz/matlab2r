#include "matlab2r_driver.hpp"
#include <fstream>
#include <sstream>

using namespace std;

bool matlab2r_driver::parse_stream(istream& in, cstref sname, ostream& out)
{
    //reset();
    streamname = sname;
    matlab_lexer scanner(&in);
    scanner.set_debug(trace_scanning);
    lexer = &scanner;
    yy::matlab_parser parser(*this);
    parser.set_debug_level(trace_parsing);
    bool success = parser.parse() == 0;
    lexer = nullptr; // it's only active on the stack
    return success;
}

bool matlab2r_driver::parse_string(cstref line, cstref sname, std::ostream& out)
{
    istringstream iss(line);
    return parse_stream(iss, sname);
}

bool matlab2r_driver::parse_file(cstref filename, std::ostream& out)
{
    ifstream in(filename);
    if(!in.good()) return false;
    return parse_stream(in, filename);
}

void matlab2r_driver::error(const yy::location& l, cstref m, cstref t)
{
    cerr << streamname << ":" << l << ": " << m << ": " << t << endl;
}

void matlab2r_driver::error(const yy::location& l, cstref m)
{
    cerr << streamname << ":" << l << ": " << m << endl;
}

void matlab2r_driver::error (cstref m)
{
    cerr << streamname << ":" << lexer->loc << ": " << m << endl;
}
