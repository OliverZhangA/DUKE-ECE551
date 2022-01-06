#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int mid = (low + high) / 2;
  int result = f->invoke(mid);
  if ((high - low <= 1)) {
    return low;
  }
  else if (result > 0) {
    return binarySearchForZero(f, low, mid);
  }
  else {
    return binarySearchForZero(f, mid, high);
  }
}
