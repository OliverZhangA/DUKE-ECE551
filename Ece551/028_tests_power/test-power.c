#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

unsigned powerans(unsigned x, unsigned y) {
  unsigned ans = 1;
  for (unsigned i = 0; i < y; i++) {
    ans *= x;
  }
  return ans;
}

void run_check(unsigned x, unsigned y) {
  if (power(x, y) != powerans(x, y)) {
    printf("output is %d but expected ans is %d \n", power(x, y), powerans(x, y));
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0);
  run_check(1, 0);
  run_check(2, 3);
  //run_check('a', 'b');
  run_check(97, 98);
  printf("you are good");
  return EXIT_SUCCESS;
}
