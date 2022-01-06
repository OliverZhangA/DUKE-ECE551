#include "IntArray.h"

#include <assert.h>

#include <iostream>

IntArray::IntArray() {
  data = NULL;
  numElements = 0;
}
IntArray::IntArray(int n) {
  numElements = n;
  data = new int[n];
}

IntArray::IntArray(const IntArray & rhs) {
  numElements = rhs.numElements;
  data = new int[numElements];
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  numElements = rhs.numElements;
  int * temp = data;
  data = new int[numElements];
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
  delete[] temp;
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index < numElements && index >= 0);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index < numElements && index >= 0);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return true;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return true;
    }
  }
  return false;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() == 0) {
    std::cout << "{}";
    return s;
  }
  else {
    std::cout << "{" << rhs[0];
  }
  for (int i = 1; i < rhs.size(); i++) {
    std::cout << ", " << rhs[i];
  }
  std::cout << "}";
  return s;
}
