
#ifndef OPTIONS_N
#define OPTIONS_N

#include <string>
#include <iostream>

struct TOptions {
   std::string sudokuFileName;
};

TOptions parseOptions(int argc, char* argv[]);
void printUsage(std::ostream& fout = std::cout);
void printVersion(std::ostream& fout = std::cout);

#endif
