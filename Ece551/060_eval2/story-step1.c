#include <stdio.h>
#include <string.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: story template file");
    exit(EXIT_FAILURE);
  }

  FILE * story = fopen(argv[1], "r");
  if (story == NULL) {
    fprintf(stderr, "fail to open story template file!");
    exit(EXIT_FAILURE);
  }

  category_t * records = malloc(sizeof(*records));
  records->name = NULL;
  records->words = NULL;
  records->n_words = 0;
  read_story(story, NULL, records, 0);
  //free ans!!!!!
  if (fclose(story) != 0) {
    fprintf(stderr, "fail to close files!");
    exit(EXIT_FAILURE);
  }
  freecat(records);
  free(records);
  return EXIT_SUCCESS;
}
