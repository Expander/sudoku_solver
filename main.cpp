
#include "options.hpp"
#include "sudoku.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
   TOptions options = ParseOptions(argc, argv);
   TSudokuFileReader<9,9> sudokuFileReader(options.sudokuFileName);
   TSudoku<TSudokuFileReader<9,9> > sudoku(sudokuFileReader);

   std::cout << "\n" << sudoku << std::endl;
   sudoku.Solve();
   std::cout << "solution: \n" << sudoku
             << "\nsolution is "
             << (sudoku.SolutionIsValid() ? "valid" : "invalid")
             << std::endl;
   return 0;
}
