# matlab2r
matlab2r attempts to be a fully-featured transpiler, from the MATLAB language to the R language. It is currently a work in progress.

# Building
The matlab2r project uses the [CMake](https://cmake.org) build system. This project also uses C++14, so make sure your compiler supports the C++14 standard. clang 3.4 or greater, and gcc 4.9 or greater should both compile this project OK.

## Dependencies
Make sure that these are in a place that CMake can find them.
* Flex
* Bison
* Boost (I use 1.60, but only for filesystem utilities. Most versions should work fine.)

## Under Linux
1. Make a directory called "build" in the project root.
2. Open a terminal and navigate to the build directory.
3. Run `cmake ..`. Hopefully everything will work.
4. Run `make`. Optionally, if you have some extra CPU cycles to spare, you can run `make -jX`, where X is the number of jobs you want to run simultaneously.

Provided that `make` succeeded, there should be a matlab2r executable in the build directory. Yay!

## Under Windows with Visual Studio
Coming soon

# License
ISC License, see the LICENSE file.