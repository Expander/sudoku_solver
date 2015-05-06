
#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <iostream>
#include <cassert>

template <typename T, T nRows> class TSudoku;

template <typename T, T nRows>
std::ostream& operator<<(std::ostream&, const TSudoku<T, nRows>&);

template <typename T = unsigned char, T nRows = 9>
class TSudoku {
public:
   TSudoku();
   ~TSudoku() {}

   enum { rows = nRows, cols = nRows };
   typedef T value_type;
   typedef std::vector<T> row_type;
   typedef std::vector<row_type> grid_type;

   bool fieldValueIsValid(T, T) const;
   row_type& operator[](const T&);
   const row_type& operator[](const T&) const;
   bool operator==(const TSudoku<T,nRows>&) const;

   friend std::ostream& operator<< <> (std::ostream&, const TSudoku<T, nRows>&);

private:
   grid_type fGrid;
};

template <typename T, T nRows>
TSudoku<T, nRows>::TSudoku()
   : fGrid(rows, row_type(cols, 0))
{
}

template <typename T, T nRows>
bool TSudoku<T, nRows>::fieldValueIsValid(T r, T c) const
{
   const value_type value = fGrid[r][c];

   if (value < 1 || value > nRows)
      return false;

   // check if value appears in row
   for (value_type row = 0; row < nRows; ++row) {
      if (row != r && fGrid[row][c] == value)
         return false;
   }

   // check if value appears in column
   for (value_type col = 0; col < nRows; ++col) {
      if (col != c && fGrid[r][col] == value)
         return false;
   }

   // check if value appears in sub-square
   const value_type sub_row_start = 3 * (r / 3);
   const value_type sub_row_end   = sub_row_start + 3;
   const value_type sub_col_start = 3 * (c / 3);
   const value_type sub_col_end   = sub_col_start + 3;
   for (value_type row = sub_row_start; row < sub_row_end; ++row) {
      for (value_type col = sub_col_start; col < sub_col_end; ++col) {
         if (col != c && row != r && fGrid[row][col] == value)
            return false;
      }
   }
   return true;
}

template <typename T, T nRows>
typename TSudoku<T, nRows>::row_type&
TSudoku<T, nRows>::operator[](const T& row_index)
{
   assert(row_index < fGrid.size() && "row_index out of range");
   return fGrid[row_index];
}

template <typename T, T nRows>
const typename TSudoku<T, nRows>::row_type&
TSudoku<T, nRows>::operator[](const T& row_index) const
{
   assert(row_index < fGrid.size() && "row_index out of range");
   return fGrid[row_index];
}

template <typename T, T nRows>
bool TSudoku<T, nRows>::operator==(const TSudoku<T,nRows>& other) const
{
   for (T row = 0; row < nRows; ++row) {
      for (T col = 0; col < nRows; ++col) {
         if (fGrid[row][col] != other[row][col])
            return false;
      }
   }
   return true;
}

template <typename T, T nRows>
std::ostream& operator<<(std::ostream& sout, const TSudoku<T, nRows>& sudoku)
{
   assert(sudoku.fGrid.size() == nRows);
   for (T row = 0; row < nRows; ++row) {
      if (row != 0 && row % 3 == 0)
         sout << '\n';
      for (T col = 0; col < nRows; ++col) {
         assert(sudoku.fGrid[row].size() == nRows);
         if (col != 0) {
            if (col % 3 == 0)
               sout << "  ";
            else
               sout << ' ';
         }
         sout << static_cast<int>(sudoku.fGrid[row][col]);
      }
      sout << '\n';
   }
   return sout;
}

#endif
