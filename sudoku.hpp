
#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <iostream>
#include <cassert>

template <typename T, T nRows, T nCols> class TSudoku;

template <typename T, T nRows, T nCols>
std::ostream& operator<<(std::ostream&, const TSudoku<T, nRows, nCols>&);

template <typename T = unsigned char, T nRows = 9, T nCols = 9>
class TSudoku {
public:
   TSudoku();
   ~TSudoku() {}

   enum { rows = nRows, cols = nCols };
   typedef std::vector<T> row_type;
   typedef std::vector<row_type> grid_type;

   row_type& operator[](const T&);
   const row_type& operator[](const T&) const;

   friend std::ostream& operator<< <> (std::ostream&, const TSudoku<T, nRows, nCols>&);

private:
   grid_type fGrid;
};

template <typename T, T nRows, T nCols>
TSudoku<T, nRows, nCols>::TSudoku()
   : fGrid(nRows, row_type(nCols, 0))
{
}

template <typename T, T nRows, T nCols>
typename TSudoku<T, nRows, nCols>::row_type&
TSudoku<T, nRows, nCols>::operator[](const T& row_index)
{
   assert(row_index < fGrid.size() && "row_index out of range");
   return fGrid[row_index];
}

template <typename T, T nRows, T nCols>
const typename TSudoku<T, nRows, nCols>::row_type&
TSudoku<T, nRows, nCols>::operator[](const T& row_index) const
{
   assert(row_index < fGrid.size() && "row_index out of range");
   return fGrid[row_index];
}

template <typename T, T nRows, T nCols>
std::ostream& operator<<(std::ostream& sout, const TSudoku<T, nRows, nCols>& sudoku)
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
