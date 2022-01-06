#include "IntMatrix.h"

IntMatrix::IntMatrix() {
  numRows = 0;
  numColumns = 0;
  rows = NULL;
}
IntMatrix::IntMatrix(int r, int c) {
  numRows = r;
  numColumns = c;
  rows = new IntArray *[r];
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
    for (int j = 0; j < numColumns; j++) {
      (*rows[i])[j] = (*rhs.rows[i])[j];
    }
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  int numRowsold = numRows;
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  IntArray ** temp = rows;
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
    for (int j = 0; j < numColumns; j++) {
      (*rows[i])[j] = (*rhs.rows[i])[j];
    }
  }
  for (int i = 0; i < numRowsold; i++) {
    delete temp[i];
  }
  delete[] temp;
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if (*rows[i] != *rhs.rows[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix ans = *this;
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*ans.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  std::cout << "[ ";
  if (rhs.getRows() != 0) {
    std::cout << rhs[0];
    for (int i = 1; i < rhs.getRows(); i++) {
      std::cout << ",\n" << rhs[i];
    }
  }
  std::cout << " ]";
  return s;
}
