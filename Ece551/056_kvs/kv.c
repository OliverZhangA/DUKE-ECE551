#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * openfile(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "fail to open the file");
    exit(EXIT_FAILURE);
  }
  return f;
}

void closefile(FILE * f) {
  if (fclose(f)) {
    fprintf(stderr, "fail to close file");
    exit(EXIT_FAILURE);
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = openfile(fname);
  char * line = NULL;
  size_t sz = 0;
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->kvarray_size = 0;
  ans->kvarray = NULL;
  int x;
  while ((x = getline(&line, &sz, f)) > 0) {
    ans->kvarray = realloc(ans->kvarray, (ans->kvarray_size + 1) * sizeof(*ans->kvarray));
    ans->kvarray_size++;
    ans->kvarray[ans->kvarray_size - 1] = malloc(sizeof(**ans->kvarray));
    ans->kvarray[ans->kvarray_size - 1]->value = strchr(line, '=');
    *ans->kvarray[ans->kvarray_size - 1]->value = '\0';
    ans->kvarray[ans->kvarray_size - 1]->value++;
    line[x - 1] = '\0';
    ans->kvarray[ans->kvarray_size - 1]->key = line;
    line = NULL;
  }
  closefile(f);
  free(line);
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->kvarray_size; i++) {
    free(pairs->kvarray[i]->key);
    free(pairs->kvarray[i]);
  }
  free(pairs->kvarray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->kvarray_size; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvarray[i]->key, pairs->kvarray[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  char * ans = NULL;
  for (int i = 0; i < pairs->kvarray_size; i++) {
    if (!strcmp(pairs->kvarray[i]->key, key)) {
      ans = pairs->kvarray[i]->value;
    }
  }

  return ans;
}
