#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_tag {
  char * name;
  char ** nameC;
  int numC;
};
typedef struct student_tag student;

struct roster_tag {
  int num_of_students;
  student ** students;
};
typedef struct roster_tag roster;

struct class_list_tag {
  int numC;
  char ** nameCs;
};
typedef struct class_list_tag class_list;

int read_an_integer(FILE * f);
student * read_a_student(FILE * f);

roster * read_input(char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "fail to open the input file");
    return NULL;
  }
  roster * answer = malloc(sizeof(*answer));
  answer->num_of_students = read_an_integer(f);
  answer->students = malloc(answer->num_of_students * sizeof(*answer->students));
  if (answer->students == NULL) {
    free(answer);
    return NULL;
  }
  for (int i = 0; i < answer->num_of_students; i++) {
    answer->students[i] = read_a_student(f);
  }
  int result = fclose(f);
  if (result != 0) {
    fprintf(stderr, "fail to close the file");
    exit(EXIT_FAILURE);
  }
  return answer;
}

void strip_newline(char * line) {
  char * p = strchr(line, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

student * read_a_student(FILE * f) {
  student * s = malloc(sizeof(*s));
  size_t sz = 0;
  s->name = NULL;
  getline(&s->name, &sz, f);
  strip_newline(s->name);
  s->numC = read_an_integer(f);
  s->nameC = malloc(s->numC * sizeof(*s->nameC));
  for (int i = 0; i < s->numC; i++) {
    s->nameC[i] = NULL;
    getline(&s->nameC[i], &sz, f);
    strip_newline(s->nameC[i]);
  }
  return s;
}

int contain(char ** array, char * s, int n) {
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (!strcmp(array[i], s)) {
      ans = 1;
    }
  }
  return ans;
}

void add_class_to_list(class_list * the_class_list, char * classname) {
  the_class_list->numC++;
  the_class_list->nameCs = realloc(
      the_class_list->nameCs, the_class_list->numC * sizeof(*the_class_list->nameCs));
  the_class_list->nameCs[the_class_list->numC - 1] = classname;
}

class_list * get_class_list(roster * the_roster) {
  class_list * ans = malloc(sizeof(*ans));
  ans->numC = 0;
  ans->nameCs = NULL;
  for (int i = 0; i < the_roster->num_of_students; i++) {
    for (int j = 0; j < the_roster->students[i]->numC; j++) {
      if (!contain(ans->nameCs, the_roster->students[i]->nameC[j], ans->numC)) {
        add_class_to_list(ans, the_roster->students[i]->nameC[j]);
      }
    }
  }
  return ans;
}

char * make_filename(char * name) {
  const char * suffix = ".roster.txt";
  unsigned len = strlen(name) + strlen(suffix) + 1;
  char * outputname = malloc(len * sizeof(*outputname));
  snprintf(outputname, len, "%s%s", name, suffix);
  return outputname;
}

void write_one_file(char * name, roster * the_roster) {
  char * filename = make_filename(name);
  FILE * outputfile = fopen(filename, "w");
  free(filename);
  if (outputfile == NULL) {
    fprintf(stderr, "fail to write the file");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < the_roster->num_of_students; i++) {
    if (contain(the_roster->students[i]->nameC, name, the_roster->students[i]->numC)) {
      fprintf(outputfile, "%s\n", the_roster->students[i]->name);
    }
  }
  int result = fclose(outputfile);
  if (result != 0) {
    fprintf(stderr, "fail to close the output file");
    exit(EXIT_FAILURE);
  }
}

void write_files(class_list * the_class_list, roster * the_roster) {
  for (int i = 0; i < the_class_list->numC; i++) {
    write_one_file(the_class_list->nameCs[i], the_roster);
  }
}

int read_an_integer(FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  int num_of_students;
  getline(&line, &sz, f);
  sscanf(line, "%d", &num_of_students);
  free(line);
  return num_of_students;
}

void free_roster(roster * the_roster) {
  for (int i = 0; i < the_roster->num_of_students; i++) {
    for (int j = 0; j < the_roster->students[i]->numC; j++) {
      free(the_roster->students[i]->nameC[j]);
    }
    free(the_roster->students[i]->nameC);
    free(the_roster->students[i]->name);
    free(the_roster->students[i]);
  }
  free(the_roster->students);
  free(the_roster);
}

void free_class_list(class_list * the_class_list) {
  for (int i = 0; i < the_class_list->numC; i++) {
    //free(the_class_list->nameCs[i]);
  }
  free(the_class_list->nameCs);
  free(the_class_list);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "invalid input\n");
    return EXIT_FAILURE;
  }

  roster * the_roster = read_input(argv[1]);
  if (the_roster == NULL) {
    fprintf(stderr, "can not read the roster");
    return EXIT_FAILURE;
  }

  class_list * the_class_list = get_class_list(the_roster);
  write_files(the_class_list, the_roster);

  free_class_list(the_class_list);
  free_roster(the_roster);
  return EXIT_SUCCESS;
}
