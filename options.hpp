
#ifndef OPTIONS_N
#define OPTIONS_N

#include <string>
#include <iostream>

struct TOptions {
   std::string sudokuFileName;
};

TOptions ParseOptions(int argc, char* argv[]);
void PrintUsage(std::ostream& fout = std::cout);
void PrintVersion(std::ostream& fout = std::cout);

#endif
