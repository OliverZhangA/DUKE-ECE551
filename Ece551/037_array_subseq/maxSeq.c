#include <stdlib.h>

int forward(int * array, size_t * i, size_t n) {
  int num = 1;
  while (1) {
    if (*i == n) {
      return num;
    }
    if (array[*i] > array[*i - 1]) {
      num += 1;
      *i += 1;
    }
    else {
      *i += 1;
      return num;
    }
  }
}

size_t maxSeq(int * array, size_t n) {
  if (n <= 1) {
    return n;
  }
  int num = 1;
  size_t i = 1;
  while (i < n) {
    int count = forward(array, &i, n);
    num = num > count ? num : count;
  }
  return num;
}
