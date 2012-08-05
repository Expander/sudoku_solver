
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

   void SolveField(unsigned char, unsigned char);
   bool FieldValueIsValid(unsigned char, unsigned char) const;
   void GetNextField(unsigned char, unsigned char, unsigned char&, unsigned char&) const;
   bool IsLastField(unsigned char, unsigned char) const;
   bool FieldIsSolved(unsigned char, unsigned char) const;
   void ClearField(unsigned char, unsigned char);

   field_t fField;
   bool    fSolutionFound;
};

std::ostream& operator<<(std::ostream&, const TSudoku&);

#endif
