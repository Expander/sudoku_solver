
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
