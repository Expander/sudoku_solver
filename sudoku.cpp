
#include "sudoku.hpp"
#include "sudoku_reader.hpp"

#include <iostream>
#include <cassert>

namespace {
   const unsigned char N_ROWS = 9;
   const unsigned char N_COLS = N_ROWS;
}

TSudoku::TSudoku(const std::string& sudokuFileName)
   : fGrid()
   , fSolutionFound(false)
{
   TSudokuReader sudokuReader(N_ROWS, N_COLS);
   fGrid = sudokuReader.Read(sudokuFileName);
}

TSudoku::~TSudoku()
{
}

void TSudoku::Solve()
{
   // find non-empty field
   assert(fGrid.size() == N_ROWS);
   fSolutionFound = false;
   SolveField(0, 0);
}

void TSudoku::SolveField(unsigned char row, unsigned char col)
{
   assert(row < N_ROWS && "row out of range");
   assert(col < N_COLS && "col out of range");
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
      // try values from 1 to N_ROWS
      for (unsigned char value = 1; value <= N_ROWS; ++value) {
         fGrid[row][col] = value;
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

void TSudoku::GetNextField(unsigned char row, unsigned char col, unsigned char& new_row, unsigned char& new_col) const
{
   new_col = col;
   new_row = row;
   if (col < N_COLS - 1) {
      ++new_col;
   } else if (row < N_ROWS - 1) {
      ++new_row;
      new_col = 0;
   }
}

bool TSudoku::IsLastField(unsigned char row, unsigned char col) const
{
   return row == N_ROWS - 1 && col == N_COLS - 1;
}

bool TSudoku::FieldIsSolved(unsigned char row, unsigned char col) const
{
   return fGrid[row][col] != 0;
}

void TSudoku::ClearField(unsigned char row, unsigned char col)
{
   fGrid[row][col] = 0;
}

bool TSudoku::FieldValueIsValid(unsigned char r, unsigned char c) const
{
   unsigned char value = fGrid[r][c];
   assert(FieldIsSolved(r, c) && "field is not solved");

   // check if value appears in row
   for (unsigned char row = 0; row < N_ROWS; ++row) {
      if (row != r && fGrid[row][c] == value)
         return false;
   }

   // check if value appears in column
   for (unsigned char col = 0; col < N_COLS; ++col) {
      if (col != c && fGrid[r][col] == value)
         return false;
   }

   // check if value appears in sub-square
   const unsigned char sub_row_start = 3 * (r / 3);
   const unsigned char sub_row_end   = sub_row_start + 3;
   const unsigned char sub_col_start = 3 * (c / 3);
   const unsigned char sub_col_end   = sub_col_start + 3;
   for (unsigned char row = sub_row_start; row < sub_row_end; ++row) {
      for (unsigned char col = sub_col_start; col < sub_col_end; ++col) {
         if (col != c && row != r && fGrid[row][col] == value)
            return false;
      }
   }
   return true;
}

bool TSudoku::SolutionIsValid() const
{
   for (unsigned char row = 0; row < N_ROWS; ++row) {
      for (unsigned char col = 0; col < N_COLS; ++col) {
         if (!FieldValueIsValid(row, col))
            return false;
      }
   }
   return true;
}

std::ostream& operator<<(std::ostream& sout, const TSudoku& sudoku)
{
   assert(sudoku.fGrid.size() == N_ROWS);
   for (unsigned char row = 0; row < N_ROWS; ++row) {
      if (row != 0 && row % 3 == 0)
         sout << "\n";
      for (unsigned char col = 0; col < N_COLS; ++col) {
         assert(sudoku.fGrid[row].size() == N_COLS);
         if (col != 0 && col % 3 == 0)
            sout << " ";
         sout << static_cast<int>(sudoku.fGrid[row][col]);
      }
      sout << "\n";
   }
   return sout;
}
