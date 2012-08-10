
#ifndef SUDOKU_READER_H
#define SUDOKU_READER_H

#include <string>
#include <vector>

class TSudokuReader {
public:
   TSudokuReader(unsigned char, unsigned char);
   ~TSudokuReader();

   typedef std::vector<unsigned char> row_t;
   typedef std::vector<row_t> grid_t;

   grid_t Read(const std::string&);

private:
   unsigned char fNRows;
   unsigned char fNColumns;

   row_t CreateRow(const std::vector<std::string>&) const;
   std::vector<std::string> Split(const std::string&) const;
};

#endif
