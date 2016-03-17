#include "matlab2r_driver.hpp"
#include "visitor.hpp"

#include <getopt.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>

#define VCOUT if(verbose) cout
#define VCERR if(verbose) cerr

using namespace std;
namespace fs = boost::filesystem;

static bool trace_scanning = false;
static bool trace_parsing = false;
static bool verbose = false;
static vector<string> filenames;

static bool parse_opts(int, char**);
static void usage(int, char**);
static void print_version();

static bool parse_opts(int argc, char **argv)
{
    static struct option lopts[] = 
    {
        { "trace-scanning", no_argument, nullptr, 's' },
        { "trace-parsing",  no_argument, nullptr, 'p' },
        { "verbose",        no_argument, nullptr, 'v' },
        { "version",        no_argument, nullptr, 0   },
        { nullptr, 0, nullptr, 0 },
    };

    char c;
    int option_index;
    while((c = getopt_long(argc, argv, "spv", lopts, &option_index)) != -1) {
        switch(c) {
        // GNU will print out the error for us. Thanks, GNU!
        case '?': return false;
        case 'v':
            verbose = true;
            break;
        case 's':
            trace_scanning = true;
            break;
        case 'p':
            trace_parsing = true;
            break;
        case 0:
            // print version and exit immediately
            if(strcmp(lopts[option_index].name, "version") == 0) {
                print_version();
                exit(0);
            }
        default:
            break;
        }
    }
    while(optind < argc)
        filenames.push_back(argv[optind++]);
    for(; optind < argc; optind++)
        cerr << "ignoring input file: " << argv[optind] << endl;
    return true;
}

static void usage(int argc, char **argv)
{
    cout << "usage: " << argv[0] << " [options] file [ file ... ]" << endl;
    cout << "available options: " << endl;
    cout << endl <<
"-s | --trace-scanning                      traces the scanning of the input " << endl <<
"-p | --trace-parsing                       traces the parsing of the input  " << endl <<
"-v | --verbose                             verbose output                   " << endl <<
"--version                                  prints the version, and immediately exists." << endl <<
    endl;
}

static void print_version()
{
    cout << "matlab2r " VERSION_STR;
#if WITH_GIT_INFO
    cout << " (" GIT_COMMIT_STR ")";
#endif /* WITH_GIT_INFO */
    cout << endl;
}

int main(int argc, char **argv)
{
    /* Parse command line options */
    if(parse_opts(argc, argv) == 0) {
        usage(argc, argv);
        cerr << "exiting" << endl;
        exit(1);
    }

    /* Make sure we got at least one filename in our list */
    if(filenames.size() == 0) {
        cerr << argv[0] << " requires at least one argument" << endl;
        usage(argc, argv);
        cerr << "exiting" << endl;
        exit(1);
    }
    
    /* Parse every file */
    for(auto& file : filenames) {
        VCERR << "processing file " << file << ": ";
        matlab2r_driver the_driver;
        the_driver.trace_scanning = trace_scanning;
        the_driver.trace_parsing = trace_parsing;

        /* Make sure the file exists and is not a directory */
        if(!fs::exists(file) || fs::is_directory(file)) {
            VCERR << endl;
            cerr << "error: `" << file << "' is not a regular file." << endl;
            cerr << "exiting" << endl;
            exit(1);
        }

        if(the_driver.parse_file(file)) {
            VCERR << "done" << endl;
            // get the AST
            auto ast = the_driver.ast;
            if(ast != nullptr) {
                VCERR << "checking sanity of " << file << ": ";
                sanity_check_visitor sanity_checker;
                sanity_checker.start(ast.get());
                if(sanity_checker.is_successful()) {
                    VCERR << "done" << endl;
                }
                else {
                    cerr << "there was an error checking the sanity of " << file << ", continuing" << endl;
                    continue;
                }
                rename_visitor renamer;
                renamer.visit(ast.get());
                function_name_visitor fun_namer;
                fun_namer.visit(ast.get());
                codegen_visitor generator = codegen_visitor(fun_namer.get_function_names());
                generator.visit(ast.get());
            }
            else {
                cerr << "error: ast is null" << endl;
            }
        }
    }
}

