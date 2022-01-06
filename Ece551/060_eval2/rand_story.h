#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
#include <stdio.h>
void parse_and_print(char * line, catarray_t * cats, category_t * records, int noreuse);
void read_story(FILE * f, catarray_t * cats, category_t * records, int noreuse);
void add_word(catarray_t * catarray, char * name, char * word);
catarray_t * read_words(FILE * f);
long is_number(char * str);
void addrecord(char * pstr, category_t * records);
char * getrecord(long num, category_t * records);
void removewords(const char * word, char * name, catarray_t * cats);
void freecat(category_t * cat);
void freecatarray(catarray_t * cats);
#endif
