#include <stdio.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  int w;
  int s;
  int noreuse;
  if (argc == 4) {
    if (!strcmp(argv[1], "-n")) {
      w = 2;
      s = 3;
      noreuse = 1;
    }
    else {
      fprintf(stderr, "usage: (-n), words file, story template file");
      exit(EXIT_FAILURE);
    }
  }
  else if (argc == 3) {
    w = 1;
    s = 2;
    noreuse = 0;
  }
  else {
    fprintf(stderr, "usage: (-n), words file, story template file");
    exit(EXIT_FAILURE);
  }
  FILE * words = fopen(argv[w], "r");
  if (words == NULL) {
    fprintf(stderr, "fail to open words file!");
    exit(EXIT_FAILURE);
  }

  FILE * story = fopen(argv[s], "r");
  if (story == NULL) {
    fprintf(stderr, "fail to open story template file!");
    exit(EXIT_FAILURE);
  }

  category_t * records = malloc(sizeof(*records));
  records->name = NULL;
  records->words = NULL;
  records->n_words = 0;

  catarray_t * ans = read_words(words);
  read_story(story, ans, records, noreuse);
  //free ans!!!!!
  if (fclose(words) != 0 || fclose(story) != 0) {
    fprintf(stderr, "fail to close files!");
    exit(EXIT_FAILURE);
  }
  freecat(records);
  free(records);
  freecatarray(ans);
  return EXIT_SUCCESS;
}
