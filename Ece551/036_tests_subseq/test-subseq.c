#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  int arr1[] = {1, 2, 1, 2, 3, 4, 5, 6, 3, 4, 1, 2, 3, 4, 5};
  int arr2[] = {1, 2};
  int arr3[] = {1, 1, 1, 1};
  int arr4[] = {-1, 1};
  int arr5[] = {1, 2, 3, 4, 2, 7, 8};
  int arr6[] = {0};
  if (maxSeq(arr1, 15) == 6 && maxSeq(arr2, 0) == 0 && maxSeq(arr3, 4) == 1 &&
      maxSeq(arr4, 2) == 2 && maxSeq(arr5, 7) == 4 && maxSeq(arr6, 1) == 1) {
    printf("you are good\n");
    return EXIT_SUCCESS;
  }
  else {
    return EXIT_FAILURE;
  }
}
