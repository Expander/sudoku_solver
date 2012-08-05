
#include "sudoku.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <cassert>

namespace {
   const unsigned char N_ROWS = 9;
   const unsigned char N_COLS = N_ROWS;
}

TSudoku::TSudoku(const std::string& sudokuFileName)
   : fField()
   , fSolutionFound(false)
{
   LoadFromFile(sudokuFileName);
}

TSudoku::~TSudoku()
{
}

void TSudoku::LoadFromFile(const std::string& sudokuFileName)
{
   std::ifstream ifs(sudokuFileName.c_str());
   if (!ifs.good()) {
      std::cerr << "Error: cannot open file: " << sudokuFileName
                << std::endl;
      return;
   }
   std::cout << "loading file: " << sudokuFileName << std::endl;
   fField.clear();

   unsigned int nLinesRead = 0;
   while (ifs.good() && nLinesRead < N_ROWS) {
      std::string line;
      getline(ifs, line);
      if (line == "" || (line.size() > 0 && line[0] == '#'))
         continue;
      ++nLinesRead;

      // split line into tokens
      std::vector<std::string> tokens(Split(line));
      if (tokens.size() != N_COLS) {
         std::cerr << "Error: malformed line (more than "
                   << static_cast<int>(N_COLS) << " words): "
                   << line << std::endl;
         fField.clear();
         break;
      }
      assert(tokens.size() == N_COLS && "too many columns");
      fField.push_back(CreateRow(tokens));
   }
   assert(fField.size() == N_ROWS && "field has wrong number of rows");
}

TSudoku::row_t TSudoku::CreateRow(const std::vector<std::string>& tokens) const
{
   row_t row;
   for (std::vector<std::string>::const_iterator it = tokens.begin(),
           end = tokens.end(); it != end; ++it) {
      int value = 0;
      std::istringstream streamToken(*it);
      streamToken >> value;
      if (streamToken.rdstate() & std::istringstream::failbit) {
         std::cerr << "Error: word not convertible to"
            " unsigned int: " << *it << std::endl;
         value = 0;
      }
      if (value < 0 || value > 9) {
         std::cerr << "Error: value is not within [0,9]: "
                   << value << std::endl;
         value = 0;
      }
      row.push_back(static_cast<unsigned char>(value));
   }
   return row;
}

std::vector<std::string> TSudoku::Split(const std::string& istr) const
{
   std::istringstream streamline(istr.c_str());
   std::vector<std::string> tokens;

   // split streamline into single words, save them in tokens
   copy(std::istream_iterator<std::string>(streamline),
        std::istream_iterator<std::string>(),
        std::back_inserter<std::vector<std::string> >(tokens));

   return tokens;
}

void TSudoku::Solve()
{
   // find non-empty field
   assert(fField.size() == N_ROWS);
   fSolutionFound = false;
   TestField(0, 0);
}

void TSudoku::TestField(unsigned char row, unsigned char col)
{
   assert(row < N_ROWS && "row out of range");
   assert(col < N_COLS && "col out of range");
   if (fField[row][col] != 0) {
      if (row == N_ROWS - 1 && col == N_COLS - 1) {
         fSolutionFound = true;
         return;
      }
      // go to next field
      unsigned char new_row, new_col;
      NextField(row, col, new_row, new_col);
      TestField(new_row, new_col);
   } else {
      for (unsigned char value = 1; value <= N_ROWS; ++value) {
         fField[row][col] = value;
         if (FieldIsValid(row, col)) {
            unsigned char new_row, new_col;
            NextField(row, col, new_row, new_col);
            TestField(new_row, new_col);
         }
         if (!fSolutionFound)
            fField[row][col] = 0;
         else
            return;
      }
   }
}

void TSudoku::NextField(unsigned char row, unsigned char col, unsigned char& new_row, unsigned char& new_col) const
{
   new_col = col;
   new_row = row;
   if (col < N_COLS - 1) {
      new_col = col + 1;
   } else {
      if (row != N_ROWS - 1)
         new_col = 0;
      if (row < N_ROWS - 1)
         new_row = row + 1;
   }
}

bool TSudoku::FieldIsValid(unsigned char r, unsigned char c) const
{
   unsigned char value = fField[r][c];
   assert(value != 0);
   // check if value appears in row
   for (unsigned char row = 0; row < N_ROWS; ++row) {
      if (row != r && fField[row][c] == value)
         return false;
   }
   // check if value appears in column
   for (unsigned char col = 0; col < N_COLS; ++col) {
      if (col != c && fField[r][col] == value)
         return false;
   }
   // check if value appears in sub-square
   const unsigned char sub_row_start = 3 * (r / 3);
   const unsigned char sub_row_end   = sub_row_start + 3;
   const unsigned char sub_col_start = 3 * (c / 3);
   const unsigned char sub_col_end   = sub_col_start + 3;
   for (unsigned char row = sub_row_start; row < sub_row_end; ++row) {
      for (unsigned char col = sub_col_start; col < sub_col_end; ++col) {
         if (col != c && row != r && fField[row][col] == value)
            return false;
      }
   }
   return true;
}

bool TSudoku::SolutionIsValid() const
{
   for (unsigned char row = 0; row < N_ROWS; ++row) {
      for (unsigned char col = 0; col < N_COLS; ++col) {
         if (!FieldIsValid(row, col))
            return false;
      }
   }
   return true;
}

std::ostream& operator<<(std::ostream& sout, const TSudoku& sudoku)
{
   assert(sudoku.fField.size() == N_ROWS);
   for (unsigned char row = 0; row < N_ROWS; ++row) {
      if (row != 0 && row % 3 == 0)
         sout << "\n";
      for (unsigned char col = 0; col < N_COLS; ++col) {
         assert(sudoku.fField[row].size() == N_COLS);
         if (col != 0 && col % 3 == 0)
            sout << " ";
         sout << static_cast<int>(sudoku.fField[row][col]);
      }
      sout << "\n";
   }
   return sout;
}
