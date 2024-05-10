
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1024

bool valid_triagle(int a, int b, int c){
    if (a + b > c &&
        a + c > b &&
        b + c > a){
        return true;
    }else {
        return false;
    }
}

int main() {
  int n_valid = 0;

  FILE *file;
  char line[MAX_LINE_LENGTH];
  char **lines = NULL;
  int num_lines = 0;

  file = fopen("input.txt", "r");
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    char *new_line = malloc(strlen(line) + 1); // +1 for null terminator
    if (new_line == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      return 1;
    }
    strcpy(new_line, line);

    lines = realloc(lines, (num_lines + 1) * sizeof(char *));
    if (lines == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      return 1;
    }

    lines[num_lines] = new_line;
    num_lines++;
  }

  if (file == NULL) {
    printf("Not able to open the file.");
  }

  fclose(file);

  for (int i = 0; i < num_lines; i++) {
    char *source = lines[i];
    char *regexString = "[[:digit:]]+";
    size_t maxMatches = 3;
    size_t maxGroups = 1;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    unsigned int m;
    char *cursor;

    int a, b, c;

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED | REG_NEWLINE)) {
      printf("Could not compile regular expression.\n");
      return 1;
    }

    m = 0;
    cursor = source;
    for (m = 0; m < maxMatches; m++) {
      if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
        break; // No more matches

      if (groupArray[0].rm_so == -1)
        break; // No more groups

      char num[groupArray[0].rm_eo - groupArray[0].rm_so + 1];
      strncpy(num, cursor + groupArray[0].rm_so,
              groupArray[0].rm_eo - groupArray[0].rm_so);
      num[groupArray[0].rm_eo - groupArray[0].rm_so] = '\0';

      if (m == 0)
        a = atoi(num);
      else if (m == 1)
        b = atoi(num);
      else if (m == 2)
        c = atoi(num);

      cursor += groupArray[0].rm_eo;
    }

    regfree(&regexCompiled);



    //printf("a = %d\n", a);
    //printf("b = %d\n", b);
    //printf("c = %d\n", c);
    if (valid_triagle(a, b, c)){
        n_valid++;
    }
  }
  free(lines);
  printf("valid triagle: %d\n", n_valid);
  return 0;
}