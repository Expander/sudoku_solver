
#include "options.hpp"
#include "sudoku.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
   TOptions options = ParseOptions(argc, argv);
   TSudoku sudoku(options.sudokuFileName);
   std::cout << sudoku << std::endl;
   return 0;
}
