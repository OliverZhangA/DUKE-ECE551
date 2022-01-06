#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void read_and_print(FILE * f) {
  char * line = NULL;
  size_t size = 0;
  char ** lines = NULL;
  size_t i = 0;
  while (getline(&line, &size, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = line;
    i++;
    line = NULL;
  }
  free(line);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

FILE * openfile(char * str) {
  FILE * f;
  if ((f = fopen(str, "r")) == NULL) {
    perror("failed to open the file");
    exit(EXIT_FAILURE);
  }
  return f;
}

void closefile(FILE * f) {
  if (fclose(f) == EOF) {
    perror("failed to close the file");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    read_and_print(stdin);
  }
  else if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE * f;
      f = openfile(argv[i]);
      read_and_print(f);
      closefile(f);
    }
  }

  return EXIT_SUCCESS;
}
