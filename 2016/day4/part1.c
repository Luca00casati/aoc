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
  char cmpchs[6];
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

int nunique(char *str, int len) {
  int count[256] = {0};
  int unique_count = 0;
  for (int i = 0; i < len; i++) {
    count[(int)str[i]]++;
  }
  for (int i = 0; i < 256; i++) {
    if (count[i] > 0) {
      unique_count++;
    }
  }

  return unique_count;
}

void freekeyvalue(struct Room *room) {
  free(room->key);
  free(room->value);
}

void takekeyvalue(struct Room *room, char *str, int len) {
  int count[256] = {0};
  int unique_count = 0;

  for (int i = 0; i < len; i++) {
    if (str[i] != '-') {
      count[(int)str[i]]++;
    }
  }
  for (int i = 0; i < 256; i++) {
    if (count[i] > 0) {
      unique_count++;
    }
  }
  room->nkey = unique_count;
  room->key = malloc(unique_count * sizeof(char) + 1);
  room->value = malloc(unique_count * sizeof(int));

  if (room->key == NULL || room->value == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return;
  }
  int index = 0;
  for (int i = 0; i < len; i++) {
    if (count[(int)str[i]] > 0) {
      room->key[index] = str[i];
      room->value[index] = count[(int)str[i]];
      count[(int)str[i]] = 0; 
      index++;
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
  for (int i = 0; i < room->nkey; i++){
  printf("%d ", room->value[i]);
  }
  printf("\n");
  printf("%d\n", room->nkey);
  //printf("%s\n", room->cmpchs);

  freekeyvalue(room);
  free(room);
  return 0;
}
