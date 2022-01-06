#include "rand_story.h"

#include <stdio.h>
#include <string.h>
//function to judge whether a str(as a whole) is a number, if so, return the number it represents,
//else return 0;
long is_number(char * str) {
  char * pstr = NULL;
  long ans = strtol(str, &pstr, 10);
  if (!strcmp(pstr, "") && ans >= 1) {
    return ans;
  }
  else if (!strcmp(pstr, "") && ans < 1) {
    return 0;
  }
  else {
    return -1;
  }
}
//record the word being printed in records
void addrecord(char * pstr, category_t * records) {
  records->n_words++;
  records->words = realloc(records->words, records->n_words * sizeof(*records->words));
  records->words[records->n_words - 1] = pstr;
}
//get back the print word in history
char * getrecord(long num, category_t * records) {
  if ((size_t)num > records->n_words) {
    fprintf(stderr, "no such word in the history!");
    exit(EXIT_FAILURE);
  }
  return records->words[records->n_words - num];
}
//find and remove the word in a category
void removewords(const char * word, char * name, catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    if (!strcmp(cats->arr[i].name, name)) {
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        // if (!strcmp(word, cats->arr[i].words[j])) {
        if (word == cats->arr[i].words[j]) {
          free(cats->arr[i].words[j]);
          for (size_t m = j; m < cats->arr[i].n_words; m++) {
            cats->arr[i].words[m] = m == (cats->arr[i].n_words - 1)
                                        ? cats->arr[i].words[m]
                                        : cats->arr[i].words[m + 1];
          }
          cats->arr[i].n_words--;
          return;
        }
      }
    }
  }
}
//parse the line read in and recognize _**_, then print out the substitute word
void parse_and_print(char * line, catarray_t * cats, category_t * records, int noreuse) {
  char * p = line;
  char cate[20];
  const char * ans;
  while (*p != '\0') {
    if (*p == '_') {
      sscanf(p, "_%[^_]", cate);
      p = p + strlen(cate) + 1;
      if (*p != '_') {
        fprintf(stderr, "illegal input! not opening or closing category with '_'!\n");
        exit(EXIT_FAILURE);
      }
      long num = 0;
      if ((num = is_number(cate)) >= 1) {
        ans = getrecord(num, records);
        printf("%s", ans);
        char * ans_nc = malloc((strlen(ans) + 1) * sizeof(*ans_nc));
        strcpy(ans_nc, ans);
        addrecord(ans_nc, records);
        p++;
        continue;
      }
      else if (is_number(cate) == 0) {
        fprintf(stderr, "wrong number detected!");
        exit(EXIT_FAILURE);
      }
      else {
        ans = chooseWord(cate, cats);
        char * ans_nc = malloc((strlen(ans) + 1) * sizeof(*ans_nc));
        strcpy(ans_nc, ans);
        addrecord(ans_nc, records);
        printf("%s", ans);
        if (noreuse == 1) {
          removewords(ans, cate, cats);
        }
        p++;
        continue;
      }
    }
    printf("%c", *p);
    p++;
  }
}
//wrapper function of reading the template and filling the blank and then print it out.
void read_story(FILE * f, catarray_t * cats, category_t * records, int noreuse) {
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    parse_and_print(line, cats, records, noreuse);
  }
  free(line);
}
//adding the category name and corresponding word to the catarray, if catarray is null, malloc for its space
//if catagory has already existed, addword
//if word has also existed, add too
void add_word(catarray_t * catarray, char * name, char * word) {
  if (catarray->n == 0) {
    catarray->n++;
    catarray->arr = realloc(catarray->arr, catarray->n * sizeof(*catarray->arr));
    catarray->arr[catarray->n - 1].name = name;
    catarray->arr[catarray->n - 1].n_words = 1;
    catarray->arr[catarray->n - 1].words =
        malloc(catarray->arr[catarray->n - 1].n_words *
               sizeof(*catarray->arr[catarray->n - 1].words));
    catarray->arr[catarray->n - 1].words[0] = word;
    return;
  }
  for (size_t i = 0; i < catarray->n; i++) {
    if (!strcmp(catarray->arr[i].name, name)) {
      /* for (size_t j = 0; j < catarray->arr[i].n_words; j++) { */
      /*   if (!strcmp(catarray->arr[i].words[j], word)) { */
      /*     free(name); */
      /*     free(word); */
      /*     return; */
      /*   } */
      /* } */
      catarray->arr[i].n_words++;
      catarray->arr[i].words =
          realloc(catarray->arr[i].words,
                  catarray->arr[i].n_words * sizeof(*catarray->arr[i].words));
      catarray->arr[i].words[catarray->arr[i].n_words - 1] = word;
      free(name);
      return;
    }
  }
  catarray->n++;
  catarray->arr = realloc(catarray->arr, catarray->n * sizeof(*catarray->arr));
  catarray->arr[catarray->n - 1].name = name;
  catarray->arr[catarray->n - 1].n_words = 1;
  catarray->arr[catarray->n - 1].words =
      malloc(catarray->arr[catarray->n - 1].n_words *
             sizeof(*catarray->arr[catarray->n - 1].words));
  catarray->arr[catarray->n - 1].words[catarray->arr[catarray->n - 1].n_words - 1] = word;
  return;
}
//read categories and words from the input file and parse,
//then call addwords to add them into categories
catarray_t * read_words(FILE * f) {
  catarray_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->n = 0;
  char * line = NULL;
  size_t sz = 0;
  char * pcolon = NULL;
  char * pnewline = NULL;
  char * name;
  char * word;
  while (getline(&line, &sz, f) >= 0) {
    pcolon = strchr(line, ':');
    if (pcolon == NULL) {
      fprintf(stderr, "invalid category and word encountered");
      exit(EXIT_FAILURE);
    }
    *pcolon = '\0';
    name = line;
    word = pcolon + 1;
    if ((pnewline = strchr(word, '\n')) != NULL) {
      *pnewline = '\0';
    }
    /* if (strlen(name) == 0 || strlen(word) == 0) { */
    /*   fprintf(stderr, "invalid category and word encountered"); */
    /*   exit(EXIT_FAILURE); */
    /* } */
    char * name1 = malloc((strlen(name) + 1) * sizeof(*name1));
    strcpy(name1, name);
    char * word1 = malloc((strlen(word) + 1) * sizeof(*word1));
    strcpy(word1, word);
    add_word(ans, name1, word1);
    free(line);
    line = NULL;
  }
  free(line);
  return ans;
}
//properly free the category
void freecat(category_t * cat) {
  free(cat->name);
  for (size_t i = 0; i < cat->n_words; i++) {
    free(cat->words[i]);
  }
  free(cat->words);
}
//properly free the catarray_t
void freecatarray(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    freecat(cats->arr + i);
  }
  free(cats->arr);
  free(cats);
}
