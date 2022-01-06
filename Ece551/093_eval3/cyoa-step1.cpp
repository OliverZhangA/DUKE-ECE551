#include <assert.h>

#include "cyoa.hpp"
int main(int argc, char ** argv) {
  assert(argc == 2);
  //create a page object and printpage
  story::Page page1(argv[1]);
  page1.printpage();
  return EXIT_SUCCESS;
}
