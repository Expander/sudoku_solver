
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
