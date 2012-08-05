
#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <vector>

class TSudoku {
public:
   TSudoku(const std::string&);
   ~TSudoku();

   void Solve();
   bool SolutionIsValid() const;

   friend std::ostream& operator<<(std::ostream&, const TSudoku&);

private:
   typedef std::vector<unsigned char> row_t;
   typedef std::vector<row_t> field_t;

   void TestField(unsigned char, unsigned char);
   bool FieldIsValid(unsigned char, unsigned char) const;
   void NextField(unsigned char, unsigned char, unsigned char&, unsigned char&) const;


   field_t fField;
   bool    fSolutionFound;
};

std::ostream& operator<<(std::ostream&, const TSudoku&);

#endif
