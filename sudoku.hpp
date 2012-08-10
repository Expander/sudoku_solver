
#ifndef SUDOKU_H
#define SUDOKU_H

#include "sudoku_file_reader.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

template <unsigned char nRows, unsigned char nCols> class TSudoku;

template <unsigned char nRows, unsigned char nCols>
std::ostream& operator<<(std::ostream&, const TSudoku<nRows, nCols>&);

template <unsigned char nRows = 9, unsigned char nCols = 9>
class TSudoku {
public:
   TSudoku(const std::string&);
   ~TSudoku();

   void Solve();
   bool SolutionIsValid() const;

   friend std::ostream& operator<< <> (std::ostream&, const TSudoku<nRows, nCols>&);

private:
   typedef std::vector<unsigned char> row_t;
   typedef std::vector<row_t> grid_t;

   void SolveField(unsigned char, unsigned char);
   bool FieldValueIsValid(unsigned char, unsigned char) const;
   void GetNextField(unsigned char, unsigned char, unsigned char&, unsigned char&) const;
   bool IsLastField(unsigned char, unsigned char) const;
   bool FieldIsSolved(unsigned char, unsigned char) const;
   void ClearField(unsigned char, unsigned char);

   grid_t  fGrid;
   bool    fSolutionFound;
};

template <unsigned char nRows, unsigned char nCols>
TSudoku<nRows, nCols>::TSudoku(const std::string& sudokuFileName)
   : fGrid()
   , fSolutionFound(false)
{
   TSudokuFileReader<nRows, nCols> sudokuReader;
   fGrid = sudokuReader.Read(sudokuFileName);
}

template <unsigned char nRows, unsigned char nCols>
TSudoku<nRows, nCols>::~TSudoku()
{
}

template <unsigned char nRows, unsigned char nCols>
void TSudoku<nRows, nCols>::Solve()
{
   // find non-empty field
   assert(fGrid.size() == nRows);
   fSolutionFound = false;
   SolveField(0, 0);
}

template <unsigned char nRows, unsigned char nCols>
void TSudoku<nRows, nCols>::SolveField(unsigned char row, unsigned char col)
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

template <unsigned char nRows, unsigned char nCols>
void TSudoku<nRows, nCols>::GetNextField(unsigned char row, unsigned char col, unsigned char& new_row, unsigned char& new_col) const
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

template <unsigned char nRows, unsigned char nCols>
bool TSudoku<nRows, nCols>::IsLastField(unsigned char row, unsigned char col) const
{
   return row == nRows - 1 && col == nCols - 1;
}

template <unsigned char nRows, unsigned char nCols>
bool TSudoku<nRows, nCols>::FieldIsSolved(unsigned char row, unsigned char col) const
{
   return fGrid[row][col] != 0;
}

template <unsigned char nRows, unsigned char nCols>
void TSudoku<nRows, nCols>::ClearField(unsigned char row, unsigned char col)
{
   fGrid[row][col] = 0;
}

template <unsigned char nRows, unsigned char nCols>
bool TSudoku<nRows, nCols>::FieldValueIsValid(unsigned char r, unsigned char c) const
{
   unsigned char value = fGrid[r][c];
   assert(FieldIsSolved(r, c) && "field is not solved");

   // check if value appears in row
   for (unsigned char row = 0; row < nRows; ++row) {
      if (row != r && fGrid[row][c] == value)
         return false;
   }

   // check if value appears in column
   for (unsigned char col = 0; col < nCols; ++col) {
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

template <unsigned char nRows, unsigned char nCols>
bool TSudoku<nRows, nCols>::SolutionIsValid() const
{
   for (unsigned char row = 0; row < nRows; ++row) {
      for (unsigned char col = 0; col < nCols; ++col) {
         if (!FieldValueIsValid(row, col))
            return false;
      }
   }
   return true;
}

template <unsigned char nRows, unsigned char nCols>
std::ostream& operator<<(std::ostream& sout, const TSudoku<nRows, nCols>& sudoku)
{
   assert(sudoku.fGrid.size() == nRows);
   for (unsigned char row = 0; row < nRows; ++row) {
      if (row != 0 && row % 3 == 0)
         sout << "\n";
      for (unsigned char col = 0; col < nCols; ++col) {
         assert(sudoku.fGrid[row].size() == nCols);
         if (col != 0 && col % 3 == 0)
            sout << " ";
         sout << static_cast<int>(sudoku.fGrid[row][col]);
      }
      sout << "\n";
   }
   return sout;
}

#endif
