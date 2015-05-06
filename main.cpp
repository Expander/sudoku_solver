
#include "options.hpp"
#include "sudoku.hpp"
#include "sudoku_file_reader.hpp"
#include "backtracking_solver.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
   TOptions options = parseOptions(argc, argv);

   typedef TSudoku<unsigned char, 9> sudoku_type;
   TSudokuFileReader<sudoku_type> sudokuFileReader(options.sudokuFileName);
   sudoku_type sudoku;
   try {
      sudoku = sudokuFileReader.read();
   } catch (TSudokuFileReader<sudoku_type>::TErrorCannotOpenFile&) {
      printUsage();
      return 1;
   } catch (TSudokuFileReader<sudoku_type>::TError&) {
      return 1;
   }
   std::cout << '\n' << sudoku << std::endl;

   TBacktrackingSolver<sudoku_type> solver;
   const sudoku_type solution(solver.solve(sudoku));

   std::cout << "solution: \n" << solution
             << "\nsolution is "
             << (solver.solutionIsValid() ? "valid" : "invalid")
             << std::endl;
   return 0;
}
