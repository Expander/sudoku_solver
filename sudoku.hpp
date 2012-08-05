
#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <vector>

class TSudoku {
public:
   TSudoku(const std::string&);
   ~TSudoku();

   friend std::ostream& operator<<(std::ostream&, const TSudoku&);

private:
   typedef std::vector<unsigned char> row_t;
   typedef std::vector<row_t> field_t;

   void LoadFromFile(const std::string&);
   row_t CreateRow(const std::vector<std::string>&) const;
   std::vector<std::string> Split(const std::string&) const;

   field_t fField;
};

std::ostream& operator<<(std::ostream&, const TSudoku&);

#endif
