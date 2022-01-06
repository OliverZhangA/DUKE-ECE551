#include <stdio.h>
#include <string.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: words file");
    exit(EXIT_FAILURE);
  }

  FILE * words = fopen(argv[1], "r");
  if (words == NULL) {
    fprintf(stderr, "fail to open story words file!");
    exit(EXIT_FAILURE);
  }

  //free ans!!!!!
  catarray_t * ans = read_words(words);
  printWords(ans);
  if (fclose(words) != 0) {
    fprintf(stderr, "fail to close files!");
    exit(EXIT_FAILURE);
  }
  freecatarray(ans);
  return EXIT_SUCCESS;
}
