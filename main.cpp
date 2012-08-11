
#include "options.hpp"
#include "backtracking_solver.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
   TOptions options = ParseOptions(argc, argv);
   TSudokuFileReader<9,9> sudokuFileReader(options.sudokuFileName);
   TBacktrackingSolver<TSudokuFileReader<9,9> > solver(sudokuFileReader);

   std::cout << "\n" << solver << std::endl;
   solver.Solve();
   std::cout << "solution: \n" << solver
             << "\nsolution is "
             << (solver.SolutionIsValid() ? "valid" : "invalid")
             << std::endl;
   return 0;
}
