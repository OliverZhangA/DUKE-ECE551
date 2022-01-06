#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() {
    numRows = 0;
    numColumns = 0;
    rows = std::vector<std::vector<T> >(0);
  }
  Matrix(int r, int c) {
    numRows = r;
    numColumns = c;
    rows = std::vector<std::vector<T> >(r, std::vector<T>(c));
  }
  Matrix(const Matrix<T> & rhs) {
    rows = rhs.rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    //rows = std::vector<std::vector<T> >(numRows);
  }

  Matrix<T> & operator=(const Matrix<T> & rhs) {
    rows = rhs.rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }
  bool operator==(const Matrix<T> & rhs) const {
    if (numRows != rhs.numRows) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      if (!(rows[i] == rhs.rows[i])) {
        return false;
      }
    }
    return true;
  }
  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix<T> ans = (*this);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans[i][j] = rows[i][j] + rhs[i][j];
      }
    }
    return ans;
  }
  template<typename A>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<A> & rhs);

  template<typename X>
  friend std::ostream & operator<<(std::ostream & s, const std::vector<X> & rhs);
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  std::cout << "{";
  if (rhs.size() != 0) {
    std::cout << rhs[0];
    for (size_t i = 1; i < rhs.size(); i++) {
      std::cout << ", " << rhs[i];
    }
  }
  std::cout << "}";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
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

//template<typename T>
//std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
#endif
