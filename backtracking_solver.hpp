
#ifndef BACKTRACKING_SOLVER_H
#define BACKTRACKING_SOLVER_H

#include "sudoku.hpp"

#include <cassert>

template <class TSudoku>
class TBacktrackingSolver {
public:
   TBacktrackingSolver(const TSudoku&);
   ~TBacktrackingSolver();

   typedef typename TSudoku::row_type row_t;
   typedef typename TSudoku::grid_type grid_t;
   enum { nRows = TSudoku::rows, nCols = TSudoku::cols };

   const TSudoku& GetSolution() const;
   void Solve();
   bool SolutionIsValid() const;

private:
   void SolveField(unsigned char, unsigned char);
   bool FieldValueIsValid(unsigned char, unsigned char) const;
   void GetNextField(unsigned char, unsigned char, unsigned char&, unsigned char&) const;
   bool IsLastField(unsigned char, unsigned char) const;
   bool FieldIsSolved(unsigned char, unsigned char) const;
   void ClearField(unsigned char, unsigned char);

   TSudoku fSudoku;
   bool    fSolutionFound;
};

template <class TSudoku>
TBacktrackingSolver<TSudoku>::TBacktrackingSolver(const TSudoku& sudoku)
   : fSudoku(sudoku)
   , fSolutionFound(false)
{
}

template <class TSudoku>
TBacktrackingSolver<TSudoku>::~TBacktrackingSolver()
{
}

template <class TSudoku>
const TSudoku& TBacktrackingSolver<TSudoku>::GetSolution() const
{
   return fSudoku;
}

template <class TSudoku>
void TBacktrackingSolver<TSudoku>::Solve()
{
   // find non-empty field
   fSolutionFound = false;
   SolveField(0, 0);
}

template <class TSudoku>
void TBacktrackingSolver<TSudoku>::SolveField(unsigned char row, unsigned char col)
{
   assert(row < nRows && "row out of range");
   assert(col < nCols && "col out of range");
   if (FieldIsSolved(row, col)) {
      if (IsLastField(row, col)) {
         fSolutionFound = true;
         return;
      }
      // go to next field
      unsigned char new_row, new_col;
      GetNextField(row, col, new_row, new_col);
      SolveField(new_row, new_col);
   } else {
      // try values from 1 to nRows
      for (unsigned char value = 1; value <= nRows; ++value) {
         fSudoku[row][col] = value;
         if (FieldValueIsValid(row, col)) {
            unsigned char new_row, new_col;
            GetNextField(row, col, new_row, new_col);
            SolveField(new_row, new_col);
         }
         if (!fSolutionFound)
            ClearField(row, col);
         else
            return;
      }
   }
}

template <class TSudoku>
void TBacktrackingSolver<TSudoku>::GetNextField(unsigned char row, unsigned char col, unsigned char& new_row, unsigned char& new_col) const
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
bool TBacktrackingSolver<TSudoku>::IsLastField(unsigned char row, unsigned char col) const
{
   return row == nRows - 1 && col == nCols - 1;
}

template <class TSudoku>
bool TBacktrackingSolver<TSudoku>::FieldIsSolved(unsigned char row, unsigned char col) const
{
   return fSudoku[row][col] != 0;
}

template <class TSudoku>
void TBacktrackingSolver<TSudoku>::ClearField(unsigned char row, unsigned char col)
{
   fSudoku[row][col] = 0;
}

template <class TSudoku>
bool TBacktrackingSolver<TSudoku>::FieldValueIsValid(unsigned char r, unsigned char c) const
{
   unsigned char value = fSudoku[r][c];
   assert(FieldIsSolved(r, c) && "field is not solved");

   // check if value appears in row
   for (unsigned char row = 0; row < nRows; ++row) {
      if (row != r && fSudoku[row][c] == value)
         return false;
   }

   // check if value appears in column
   for (unsigned char col = 0; col < nCols; ++col) {
      if (col != c && fSudoku[r][col] == value)
         return false;
   }

   // check if value appears in sub-square
   const unsigned char sub_row_start = 3 * (r / 3);
   const unsigned char sub_row_end   = sub_row_start + 3;
   const unsigned char sub_col_start = 3 * (c / 3);
   const unsigned char sub_col_end   = sub_col_start + 3;
   for (unsigned char row = sub_row_start; row < sub_row_end; ++row) {
      for (unsigned char col = sub_col_start; col < sub_col_end; ++col) {
         if (col != c && row != r && fSudoku[row][col] == value)
            return false;
      }
   }
   return true;
}

template <class TSudoku>
bool TBacktrackingSolver<TSudoku>::SolutionIsValid() const
{
   for (unsigned char row = 0; row < nRows; ++row) {
      for (unsigned char col = 0; col < nCols; ++col) {
         if (!FieldValueIsValid(row, col))
            return false;
      }
   }
   return true;
}

#endif
