
#include "options.hpp"
#include "sudoku.hpp"
#include "sudoku_file_reader.hpp"
#include "backtracking_solver.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
   TOptions options = parseOptions(argc, argv);

   typedef TSudoku<unsigned char, 9, 9> sudoku_type;
   TSudokuFileReader<sudoku_type> sudokuFileReader(options.sudokuFileName);
   sudoku_type sudoku = sudokuFileReader.read();
   std::cout << "\n" << sudoku << std::endl;

   TBacktrackingSolver<sudoku_type> solver(sudoku);
   solver.solve();

   std::cout << "solution: \n" << solver.getSolution()
             << "\nsolution is "
             << (solver.solutionIsValid() ? "valid" : "invalid")
             << std::endl;
   return 0;
}
