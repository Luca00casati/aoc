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

int countunique(const char *str) {
 int count = 0;
    for (size_t i = 0; i < strlen(str); i++){
         bool appears = false;
         for (size_t j = 0; j < i; j++){
              if (str[j] == str[i]){
                  appears = true;
                  break;
              }
         }
         if (!appears){
             count++;
         }
    }
    return count;
}


int charfind(char c, const char *str, int len) {
  for (int i = 0; i < len; i++) {
    if (str[i] == c) {
      return i;
    }
  }
  return -1;
}

bool checkvalueorder(int* v, int len){
    for (int i = 0, j = 1 ; i < len-1;j++, i++){
        if (v[i] >= v[j]){
            return true;
        }
    }
    return false;
}

bool checkkeyorder(char* k, int* v, int len){
    for (int i = 0, j = 1 ; i < len-1;j++, i++){
        if (v[i] == v[j]){
            if (k[i] >= k[j]){
                return true;
            }
        }
    }
    return false;
}

void takekeyvalue(struct Room *room, char *str, int len) {
  int index = 0;
  room->nkey = countunique(str);
  room->key = malloc(room->nkey * sizeof(char) + 1);
  room->value = malloc(room->nkey * sizeof(int));
  if (room->key == NULL || room->value == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
  }
  for (int i = 0; i < len; i++) {
    if (!charpresent(str[i], room->key, room->nkey)) {
      room->key[index] = str[i];
      room->value[index] = 0;
      index++;
    }
    if (charpresent(str[i], room->key, room->nkey)) {
      int f = charfind(str[i], room->key, room->nkey);
      room->value[f]++;
    }
  }
  room->key[index] = '\0';
  //if (checkvalueorder(room->value, room->nkey)){
  //  printf("true\n");
  //}
  //if (checkkeyorder(room->key, room->value, room->nkey)){
  //  printf("true\n");
  //}
  int tempval;
  char tempkey;
  while (!checkvalueorder(room->value, room->nkey-1)) {
     for (int i = 0, j = 1 ; i < len-1;j++, i++){
        if (room->value[i] >= room->value[j]){
            tempval = room->value[i];
            room->value[i] = room->value[j];
            room->value[j] = tempval;
            tempkey = room->key[i];
            room->key[i] = room->key[j];
            room->key[j] = tempkey;
        }
    }
}
while (!checkkeyorder(room->key, room->value, room->nkey-1)) {
     for (int i = 0, j = 1 ; i < len-1;j++, i++){
        if (room->value[i] == room->value[j]){
            if (room->key[i] >= room->key[j]){
            tempkey = room->key[i];
            room->key[i] = room->key[j];
            room->key[j] = tempkey;
        }
    }}
}

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
