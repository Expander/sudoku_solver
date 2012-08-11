
#ifndef SUDOKU_FILE_READER_H
#define SUDOKU_FILE_READER_H

#include "sudoku.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <cassert>

template <class TSudoku>
class TSudokuFileReader {
public:
   TSudokuFileReader(const std::string&);
   ~TSudokuFileReader() {}

   class TErrorCannotOpenFile {};
   typedef typename TSudoku::value_type value_type;
   typedef typename TSudoku::row_type row_t;
   typedef typename TSudoku::grid_type grid_t;
   enum { nRows = TSudoku::rows, nCols = TSudoku::cols };

   TSudoku read() const;

private:
   std::string fFileName;

   row_t createRow(const std::vector<std::string>&) const;
   std::vector<std::string> split(const std::string&) const;
};

template <class TSudoku>
TSudokuFileReader<TSudoku>::TSudokuFileReader(const std::string& fileName)
   : fFileName(fileName)
{
}

template <class TSudoku>
TSudoku TSudokuFileReader<TSudoku>::read() const
{
   std::ifstream ifs(fFileName.c_str());
   if (!ifs.good()) {
      std::cerr << "Error: cannot open file: \"" << fFileName
                << "\"" << std::endl;
      throw TErrorCannotOpenFile();
   }
   std::cout << "loading file: " << fFileName << std::endl;

   TSudoku sudoku;
   unsigned int nLinesRead = 0;
   while (ifs.good() && nLinesRead < nRows) {
      std::string line;
      getline(ifs, line);
      if (line == "" || (line.size() > 0 && line[0] == '#'))
         continue;

      // split line into tokens
      std::vector<std::string> tokens(split(line));
      if (tokens.size() != nCols) {
         std::cerr << "Error: malformed line (more than "
                   << static_cast<int>(nCols) << " words): "
                   << line << std::endl;
         break;
      }
      assert(tokens.size() == nCols && "too many columns");
      sudoku[nLinesRead] = createRow(tokens);
      ++nLinesRead;
   }
   return sudoku;
}

template <class TSudoku>
typename TSudokuFileReader<TSudoku>::row_t
TSudokuFileReader<TSudoku>::createRow(const std::vector<std::string>& tokens) const
{
   row_t row;
   row.reserve(nCols);
   for (std::vector<std::string>::const_iterator it = tokens.begin(),
           end = tokens.end(); it != end; ++it) {
      long value = atol(it->c_str());
      if (value < 0 || value > nCols) {
         std::cerr << "Error: value is not within [0," << nCols << "]: "
                   << value << std::endl;
         value = 0;
      }
      row.push_back(static_cast<value_type>(value));
   }
   return row;
}

template <class TSudoku>
std::vector<std::string>
TSudokuFileReader<TSudoku>::split(const std::string& istr) const
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
