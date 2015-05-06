
#ifndef BACKTRACKING_SOLVER_H
#define BACKTRACKING_SOLVER_H

#include "sudoku.hpp"

#include <cassert>

template <class TSudoku>
class TBacktrackingSolver {
public:
   TBacktrackingSolver();
   ~TBacktrackingSolver() {}

   typedef typename TSudoku::value_type value_type;
   typedef typename TSudoku::row_type row_t;
   typedef typename TSudoku::grid_type grid_t;
   enum { nRows = TSudoku::rows, nCols = TSudoku::cols };

   const TSudoku& solve(const TSudoku&);

private:
   void solveField(value_type, value_type);
   void getNextField(value_type, value_type, value_type&, value_type&) const;
   bool isLastField(value_type, value_type) const;
   bool fieldIsSolved(value_type, value_type) const;
   void clearField(value_type, value_type);
   void setFieldValue(value_type, value_type, value_type);

   TSudoku fSudoku;
   bool    fSolutionFound;
};

template <class TSudoku>
TBacktrackingSolver<TSudoku>::TBacktrackingSolver()
   : fSudoku()
   , fSolutionFound(false)
{
}

template <class TSudoku>
const TSudoku& TBacktrackingSolver<TSudoku>::solve(const TSudoku& sudoku)
{
   fSudoku = sudoku;
   fSolutionFound = false;
   solveField(0, 0);

   return fSudoku;
}

template <class TSudoku>
void TBacktrackingSolver<TSudoku>::solveField(value_type row, value_type col)
{
   assert(row < nRows && "row out of range");
   assert(col < nCols && "col out of range");
   if (fieldIsSolved(row, col)) {
      if (isLastField(row, col)) {
         fSolutionFound = true;
         return;
      }
      // go to next field
      value_type new_row, new_col;
      getNextField(row, col, new_row, new_col);
      solveField(new_row, new_col);
   } else {
      // try values from 1 to nRows
      for (value_type value = 1; value <= nRows; ++value) {
         setFieldValue(row,col,value);
         if (fSudoku.fieldValueIsValid(row, col)) {
            value_type new_row, new_col;
            getNextField(row, col, new_row, new_col);
            solveField(new_row, new_col);
         }
         if (!fSolutionFound)
            clearField(row, col);
         else
            return;
      }
   }
}

template <class TSudoku>
void TBacktrackingSolver<TSudoku>::getNextField(value_type row, value_type col, value_type& new_row, value_type& new_col) const
{
   new_col = col;
   new_row = row;
   if (col < nCols - 1) {
      ++new_col;
   } else if (row < nRows - 1) {
      ++new_row;
      new_col = 0;
   }
}

template <class TSudoku>
bool TBacktrackingSolver<TSudoku>::isLastField(value_type row, value_type col) const
{
   return row == nRows - 1 && col == nCols - 1;
}

template <class TSudoku>
bool TBacktrackingSolver<TSudoku>::fieldIsSolved(value_type row, value_type col) const
{
   return fSudoku[row][col] != 0;
}

template <class TSudoku>
void TBacktrackingSolver<TSudoku>::clearField(value_type row, value_type col)
{
   fSudoku[row][col] = 0;
}

template <class TSudoku>
void TBacktrackingSolver<TSudoku>::setFieldValue(value_type row, value_type col, value_type value)
{
   fSudoku[row][col] = value;
}

#endif
