#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 12

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: inputfilename");
    return EXIT_FAILURE;
  }
  FILE * f;
  if ((f = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "fail to open the file");
    return EXIT_FAILURE;
  }
  char matrix[10][10];
  char line[LINE_SIZE];
  int row = 0;
  int len = 0;
  char * p;

  while ((p = fgets(line, LINE_SIZE, f)) != NULL) {
    if (strchr(line, '\n') == NULL) {
      fprintf(stderr, "either you just have one line or this line is too long");
      return EXIT_FAILURE;
    }
    len = 0;
    for (char * p = line; *p != '\0' && *p != '\n'; p++) {
      len++;
    }
    if (len != 10) {
      fprintf(stderr, "this line do not have the right length");
      return EXIT_FAILURE;
    }
    for (int i = 0; i < 10; i++) {
      if (row > 9) {
        fprintf(stderr, "you are having to many rows");
        return EXIT_FAILURE;
      }
      matrix[i][9 - row] = line[i];
    }
    row++;
  }
  if (p == NULL && row != 10) {
    fprintf(stderr, "the file is missing rows!");
    return EXIT_FAILURE;
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }

  if (fclose(f) == EOF) {
    fprintf(stderr, "fails to close the file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
