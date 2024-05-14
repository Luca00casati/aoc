#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Room {
  char *letters;
  long id;
  char chs[6]; // 5 + null
  char *key;
  int *value;
  int nkey;
  char cmpchs[6]; // same
};

void takeletters(struct Room *room, char *str, int len) {
  room->letters = malloc((len + 1) * sizeof(char));
  if (room->letters == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(1);
  }
  size_t letters_index = 0;
  for (int i = 0; i < len; i++) {
    if (str[i] != '-') {
      room->letters[letters_index] = str[i];
      if (str[i] >= '0' && str[i] <= '9') {
        break;
      }
      letters_index++;
    }
  }
  room->letters[letters_index] = '\0';
}

void takeid(struct Room *room, char *str, int len) {
  char id[10];
  int j = 0;
  for (int i = 0; i < len; i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      id[j++] = str[i];
    } else if (str[i] == '[') {
      break;
    }
  }
  id[j] = '\0';
  room->id = atol(id);
}

void takechs(struct Room *room, char *str, int len) {
  for (int i = 0; i < len; i++) {
    if (str[i] == '[') {
      i++;
      for (int j = 0; j < 5; j++) {
        room->chs[j] = str[i + j];
      }
      room->chs[5] = '\0';
      break;
    }
  }
}

int countunique(const char *str) {
  int count = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    bool appears = false;
    for (size_t j = 0; j < i; j++) {
      if (str[j] == str[i]) {
        appears = true;
        break;
      }
    }
    if (!appears) {
      count++;
    }
  }
  return count;
}

bool charpresent(char c, char *str, int len) {
  for (int i = 0; i < len; i++) {
    if (str[i] == c) {
      return true;
    }
  }
  return false;
}

int charfind(char c, const char *str, int len) {
  for (int i = 0; i < len; i++) {
    if (str[i] == c) {
      return i;
    }
  }
  return -1;
}

void takekeyvalue(struct Room *room, char *str, int len) {
  int index = 0;
  room->nkey = countunique(str);
  room->key = malloc((room->nkey + 1) * sizeof(char));
  room->value = malloc(room->nkey * sizeof(int));
  if (room->key == NULL || room->value == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(1);
  }
  memset(room->value, 0, room->nkey * sizeof(int));
  for (int i = 0; i < len; i++) {
    if (!charpresent(str[i], room->key, index)) {
      room->key[index] = str[i];
      room->value[index] = 1;
      index++;
    } else {
      int f = charfind(str[i], room->key, index);
      room->value[f]++;
    }
  }
  room->key[index] = '\0';

  for (int i = 0; i < room->nkey - 1; i++) {
    for (int j = i + 1; j < room->nkey; j++) {
      if (room->value[i] < room->value[j] ||
          (room->value[i] == room->value[j] && room->key[i] > room->key[j])) {
        int tempval = room->value[i];
        room->value[i] = room->value[j];
        room->value[j] = tempval;
        char tempkey = room->key[i];
        room->key[i] = room->key[j];
        room->key[j] = tempkey;
      }
    }
  }
}

void takecmpchs(struct Room *room, char *str) {
  strncpy(room->cmpchs, str, 5);
  room->cmpchs[5] = '\0';
}

bool cmp(struct Room *room) { return strncmp(room->chs, room->cmpchs, 5) == 0; }

void freekeyvalue(struct Room *room) {
  free(room->letters);
  free(room->key);
  free(room->value);
}

int main() {
  struct Room *room = malloc(sizeof(struct Room));
  if (room == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return 1;
  }
  long result = 0;
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("Failed to open file");
    return 1;
  }
  while ((getline(&line, &len, file)) != -1) {
    int str_len = strlen(line);
    if (line[str_len - 1] == '\n') {
      line[str_len - 1] = '\0';
    }
    takeletters(room, line, str_len);
    takeid(room, line, str_len);
    takechs(room, line, str_len);
    takekeyvalue(room, room->letters, strlen(room->letters));
    takecmpchs(room, room->key);

    printf("Input: %s\n", line);
    printf("Letters: %s\n", room->letters);
    printf("ID: %ld\n", room->id);
    printf("Checksum: %s\n", room->chs);
    printf("Keys: %s\n", room->key);
    printf("Values: ");
    for (int i = 0; i < room->nkey; i++) {
      printf("%d ", room->value[i]);
    }
    printf("\n");
    printf("Number of keys: %d\n", room->nkey);
    printf("CmpChecksum: %s\n", room->cmpchs);
    if (cmp(room)) {
      printf("VALID\n");
      result += room->id;
    } else {
      printf("INVALID\n");
    }
    freekeyvalue(room);
  }
  fclose(file);
  printf("result: %ld\n", result);
  free(line);
  free(room);
  return 0;
}
