#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int main(void) {
  int(*f)[2] = (int(*)[2])malloc(16);
  f[0][0] = 1;
  f[0][1] = 2;
  f[1][0] = 3;
  f[1][1] = 4;
  return EXIT_SUCCESS;
}
