#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS 1024

struct Room {
  char letters[MAX_LETTERS];
  long id;
  char chs[6]; // 5 + null
  char *key;
  int *value;
  int nkey;
  char cmpchs[6]; // same
};

void takeletters(struct Room *room, char *str, int len) {
  size_t letters_index = 0;
  for (int i = 0; i < len && letters_index < MAX_LETTERS; i++) {
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
  for (int i = len - 6, j = 0; i < len - 1; i++, j++) {
    room->chs[j] = str[i];
  }
  room->chs[5] = '\0';
}

int checkkey(char key, char *str, int len) {
  for (int i = 0; i < len; i++) {
    if (str[i] == key) {
      return i;
    }
  }
  return -1;
}

void freekeyvalue(struct Room *room) {
  free(room->key);
  free(room->value);
}

bool charpresent(char c, char *str, int len) {
  for (int i = 0; i < len; i++) {
    if (str[i] == c) {
      return true;
    }
  }
  return false;
}

int countUniqueChars(const char *str) {
  int count[MAX_LETTERS] = {0};
  int uniqueCount = 0;

  for (int i = 0; str[i]; i++) {
    count[str[i]]++;
  }

  for (int i = 0; i < MAX_LETTERS; i++) {
    if (count[i] > 0) {
      uniqueCount++;
    }
  }

  return uniqueCount;
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
  room->nkey = countUniqueChars(str);
  room->key = malloc(room->nkey * sizeof(char) + 1);
  room->value = malloc(room->nkey * sizeof(int));
  if (room->key == NULL || room->value == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
  }
  for (int i = 0; i < len; i++) {
    if (!charpresent(str[i], room->key, room->nkey)) {
      room->key[index] = str[i];
      index++;
    }
    if (charpresent(str[i], room->key, room->nkey)) {
      int f = charfind(str[i], room->key, room->nkey);
      room->value[f]++;
    }
  }

  room->key[index] = '\0';
}

int main() {
  struct Room *room = malloc(sizeof(struct Room));
  if (room == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return 1;
  }

  char *str = "aaaaa-bbb-z-y-x-123[abxyz]";
  int len = strlen(str);
  takeletters(room, str, len);
  takeid(room, str, len);
  takechs(room, str, len);
  takekeyvalue(room, room->letters, strlen(room->letters));

  printf("%s\n", room->letters);
  printf("%ld\n", room->id);
  printf("%s\n", room->chs);
  printf("%s\n", room->key);
  for (int i = 0; i < room->nkey; i++) {
    printf("%d ", room->value[i]);
  }
  printf("\n");
  printf("%d\n", room->nkey);
  // printf("%s\n", room->cmpchs);

  freekeyvalue(room);
  free(room);
  return 0;
}
