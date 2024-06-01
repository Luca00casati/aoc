#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_STR 2048

bool abba_check(char *str, size_t len, size_t i) {
  char buff[4];
  if (i > len - 4) {
    return false;
  }

  for (size_t j = 0; j < 4; j++) {
    buff[j] = str[j + i];
  }

  if (buff[0] == buff[3] && buff[1] == buff[2] && buff[0] != buff[1]) {
    return true;
  }

  return abba_check(str, len, i+1);
}



bool lts_valid(char *ip) {
    char ip_copy[BUFFER_STR];
    strncpy(ip_copy, ip, BUFFER_STR - 1);
    ip_copy[BUFFER_STR - 1] = '\0';

    char *token;
    bool outside_valid = false;
    bool inside_invalid = false;
    
    token = strtok(ip_copy, "[]");
    bool is_outside = true;

    while (token != NULL) {
        if (is_outside) {
            if (abba_check(token, strlen(token), 0)) {
                outside_valid = true;
            }
        } else {
            if (abba_check(token, strlen(token), 0)) {
                inside_invalid = true;
            }
        }
        is_outside = !is_outside;
        token = strtok(NULL, "[]");
    }

    return outside_valid && !inside_invalid;
}

int main() {
  char line[BUFFER_STR];
  long long n_lts = 0;
  FILE *file = fopen("input.txt", "r");
  while (fgets(line, BUFFER_STR, file) != NULL) {
  if (lts_valid(line)) {
    printf("VALID\n");
    n_lts++;
  }
  else{
    printf("INVALID\n");
  }
  }
  printf("%lld\n", n_lts);
  fclose(file);
  return 0;
}