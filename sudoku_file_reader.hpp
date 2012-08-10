
#ifndef SUDOKU_READER_H
#define SUDOKU_READER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cassert>

template <unsigned char nRows, unsigned char nCols>
class TSudokuFileReader {
public:
   TSudokuFileReader() {}
   ~TSudokuFileReader() {}

   typedef std::vector<unsigned char> row_t;
   typedef std::vector<row_t> grid_t;

   grid_t Read(const std::string&);

private:
   row_t CreateRow(const std::vector<std::string>&) const;
   std::vector<std::string> Split(const std::string&) const;
};

template <unsigned char nRows, unsigned char nCols>
typename TSudokuFileReader<nRows, nCols>::grid_t
TSudokuFileReader<nRows, nCols>::Read(const std::string& sudokuFileName)
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
   while (ifs.good() && nLinesRead < nRows) {
      std::string line;
      getline(ifs, line);
      if (line == "" || (line.size() > 0 && line[0] == '#'))
         continue;
      ++nLinesRead;

      // split line into tokens
      std::vector<std::string> tokens(Split(line));
      if (tokens.size() != nCols) {
         std::cerr << "Error: malformed line (more than "
                   << static_cast<int>(nCols) << " words): "
                   << line << std::endl;
         field.clear();
         break;
      }
      assert(tokens.size() == nCols && "too many columns");
      field.push_back(CreateRow(tokens));
   }
   assert(field.size() == nRows && "field has wrong number of rows");
   return field;
}

template <unsigned char nRows, unsigned char nCols>
typename TSudokuFileReader<nRows, nCols>::row_t
TSudokuFileReader<nRows, nCols>::CreateRow(const std::vector<std::string>& tokens) const
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

template <unsigned char nRows, unsigned char nCols>
std::vector<std::string>
TSudokuFileReader<nRows, nCols>::Split(const std::string& istr) const
{
   std::istringstream streamline(istr.c_str());
   std::vector<std::string> tokens;

   // split streamline into single words, save them in tokens
   copy(std::istream_iterator<std::string>(streamline),
        std::istream_iterator<std::string>(),
        std::back_inserter<std::vector<std::string> >(tokens));

   return tokens;
}

#endif
