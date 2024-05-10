#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define NLINE 1911

bool valid_triagle(int a, int b, int c) {
  if (a + b > c && a + c > b && b + c > a) {
    return true;
  } else {
    return false;
  }
}

int main() {
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  int indx = 0;
  int n_valid = 0;
  // ssize_t read;
  int *arr = malloc(NLINE * sizeof(int));
  file = fopen("a.txt", "r");
  if (file == NULL)
    exit(1);
  while ((getline(&line, &len, file)) != -1) {
    // printf("%s", line);
    arr[indx] = atoi(line);
    indx++;
  }
  indx = 0;
  fclose(file);

  for (int i = 0; i < NLINE; i += 3) {
    if (valid_triagle(arr[i], arr[i + 1], arr[i + 2])) {
      n_valid++;
    }
  }
  file = fopen("b.txt", "r");

  while ((getline(&line, &len, file)) != -1) {
    // printf("%s", line);
    arr[indx] = atoi(line);
    indx++;
  }
  indx = 0;
  fclose(file);

  for (int i = 0; i < NLINE; i += 3) {
    if (valid_triagle(arr[i], arr[i + 1], arr[i + 2])) {
      n_valid++;
    }
  }
  file = fopen("c.txt", "r");
  if (file == NULL)
    exit(1);
  while ((getline(&line, &len, file)) != -1) {
    // printf("%s", line);
    arr[indx] = atoi(line);
    indx++;
  }
  indx = 0;
  fclose(file);

  for (int i = 0; i < NLINE; i += 3) {
    if (valid_triagle(arr[i], arr[i + 1], arr[i + 2])) {
      n_valid++;
    }
  }
  free(line);
  free(arr);
  printf("valid triagle: %d\n", n_valid);
  return 0;
}