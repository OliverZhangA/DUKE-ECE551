#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define unknown "<unknown> "
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ans = malloc(sizeof(*ans));
  ans->size_counts = 1;
  ans->counts = malloc(sizeof(*ans->counts));
  ans->counts[0] = malloc(sizeof(*ans->counts[0]));
  ans->counts[0]->name = malloc((strlen(unknown) + 1) * sizeof(*ans->counts[0]->name));
  strcpy(ans->counts[0]->name, unknown);
  ans->counts[0]->time = 0;
  return ans;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->counts[0]->time++;
    return;
  }
  else {
    for (int i = 1; i < c->size_counts; i++) {
      if (!strcmp(c->counts[i]->name, name)) {
        c->counts[i]->time++;
        return;
      }
    }
    c->size_counts++;
    c->counts = realloc(c->counts, c->size_counts * sizeof(*c->counts));
    c->counts[c->size_counts - 1] = malloc(sizeof(one_count_t));
    c->counts[c->size_counts - 1]->time = 1;
    c->counts[c->size_counts - 1]->name =
        malloc((strlen(name) + 1) * sizeof(*c->counts[c->size_counts - 1]->name));
    strcpy(c->counts[c->size_counts - 1]->name, name);
    return;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 1; i < c->size_counts; i++) {
    fprintf(outFile, "%s: %d\n", c->counts[i]->name, c->counts[i]->time);
  }
  if (c->counts[0]->time != 0) {
    fprintf(outFile, "%s: %d\n", c->counts[0]->name, c->counts[0]->time);
  }
  return;
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size_counts; i++) {
    free(c->counts[i]->name);
    free(c->counts[i]);
  }
  free(c->counts);
  free(c);
}
