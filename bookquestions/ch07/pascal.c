#include <stdio.h>
#include <stdlib.h>

int pascal(int i, int j) {
  if (i == j || j == 0 || i == 0) {
    return 1;
  }
  else {
    return pascal(i - 1, j - 1) + pascal(i - 1, j);
  }
}

int main(void) {
  if (pascal(0, 0) == 1 && pascal(0, 8) == 1) {
    printf("good");
  }
  return EXIT_SUCCESS;
}
