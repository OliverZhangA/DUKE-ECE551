#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * input = fopen(filename, "r");
  if (input == NULL) {
    fprintf(stderr, "fail to open file");
    exit(EXIT_FAILURE);
  }
  int x;
  char * line = NULL;
  size_t sz = 0;
  counts_t * ans = createCounts();
  while ((x = getline(&line, &sz, input)) >= 0) {
    char * end = strchr(line, '\n');
    *end = '\0';
    addCount(ans, lookupValue(kvPairs, line));
  }
  free(line);
  if (fclose(input) != 0) {
    fprintf(stderr, "fail to close file");
    exit(EXIT_FAILURE);
  }

  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "too few args");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)

  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    char * outName = computeOutputFileName(argv[i]);
    FILE * out = fopen(outName, "w");
    if (out == NULL) {
      fprintf(stderr, "fail to create file");
      exit(EXIT_FAILURE);
    }
    printCounts(c, out);
    if (fclose(out) != 0) {
      fprintf(stderr, "fail to close output file");
      exit(EXIT_FAILURE);
    }
    freeCounts(c);
    free(outName);
  }
  freeKVs(kv);

  //compute the output file name from argv[i] (call this outName)

  //open the file named by outName (call that f)

  //print the counts from c into the FILE f

  //close f

  //free the memory for outName and c

  //free the memory for kv

  return EXIT_SUCCESS;
}
