#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define sizeaa 26

void update_fre(int c, int * arr, int size) {
  if (c >= 0 && c < size) {
    arr[c] += 1;
  }
}

void frequence_count(int * arr, int size, FILE * f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      update_fre(c - 'a', arr, size);
    }
  }
}

int calculate_key(int * arr, int size) {
  int e = 0;
  for (int i = 0; i < size; i++) {
    e = arr[e] > arr[i] ? e : i;
  }

  int ans = e + 'a' - 'e';
  if (ans < 0) {
    return ans + 26;
  }
  else {
    return ans;
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFIlename");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("could not open file:");
    return EXIT_FAILURE;
  }
  int frequence_arr[sizeaa] = {0};
  frequence_count(frequence_arr, sizeaa, f);

  printf("%d\n", calculate_key(frequence_arr, sizeaa));
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
