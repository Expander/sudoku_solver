
#include "sudoku_reader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cassert>

TSudokuReader::TSudokuReader(unsigned char nRows, unsigned char nColumns)
 : fNRows(nRows)
 , fNColumns(nColumns)
{
}

TSudokuReader::~TSudokuReader()
{
}

TSudokuReader::grid_t TSudokuReader::Read(const std::string& sudokuFileName)
{
   grid_t field;
   std::ifstream ifs(sudokuFileName.c_str());
   if (!ifs.good()) {
      std::cerr << "Error: cannot open file: " << sudokuFileName
                << std::endl;
      return field;
   }
   std::cout << "loading file: " << sudokuFileName << std::endl;

   unsigned int nLinesRead = 0;
   while (ifs.good() && nLinesRead < fNRows) {
      std::string line;
      getline(ifs, line);
      if (line == "" || (line.size() > 0 && line[0] == '#'))
         continue;
      ++nLinesRead;

      // split line into tokens
      std::vector<std::string> tokens(Split(line));
      if (tokens.size() != fNColumns) {
         std::cerr << "Error: malformed line (more than "
                   << static_cast<int>(fNColumns) << " words): "
                   << line << std::endl;
         field.clear();
         break;
      }
      assert(tokens.size() == fNColumns && "too many columns");
      field.push_back(CreateRow(tokens));
   }
   assert(field.size() == fNRows && "field has wrong number of rows");
   return field;
}

TSudokuReader::row_t TSudokuReader::CreateRow(const std::vector<std::string>& tokens) const
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

std::vector<std::string> TSudokuReader::Split(const std::string& istr) const
{
   std::istringstream streamline(istr.c_str());
   std::vector<std::string> tokens;

   // split streamline into single words, save them in tokens
   copy(std::istream_iterator<std::string>(streamline),
        std::istream_iterator<std::string>(),
        std::back_inserter<std::vector<std::string> >(tokens));

   return tokens;
}
