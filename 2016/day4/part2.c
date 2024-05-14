#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Room {
    char *letters;
    long id;
    char *dec;
};

void decript(struct Room *room, int len) {
    room->dec = malloc((len + 1) * sizeof(char));
    if (room->dec == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        if (room->letters[i] >= 'a' && room->letters[i] <= 'z') {
            room->dec[i] = (char)(((room->letters[i] - 'a' + room->id) % 26) + 'a');
        }
        else {
            if ( room->dec[i] == '-'){
                 room->dec[i] = ' ';
            }
            else {
            room->dec[i] = room->letters[i];
            }
            
        }
    }
    room->dec[len] = '\0';
}

void takeletters(struct Room *room, char *str, int len) {
    room->letters = malloc((len + 1) * sizeof(char));
    if (room->letters == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    size_t letters_index = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '[') break;
            room->letters[letters_index++] = str[i];
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

void freekeyvalue(struct Room *room) {
    free(room->letters);
    free(room->dec);
}

int main() {
    struct Room *room = malloc(sizeof(struct Room));
    if (room == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    FILE *file;
    FILE *wfile;
    char *line = NULL;
    size_t len = 0;
    file = fopen("output.txt", "r");
    wfile = fopen("dec.txt", "a");
    if (file == NULL) {
        perror("Failed to open file");
        free(room);
        return 1;
    }
    if (wfile == NULL) {
        perror("Failed to open file");
        return 1;
    }

    while (getline(&line, &len, file) != -1) {
        int str_len = strlen(line);
        if (line[str_len - 1] == '\n') {
            line[str_len - 1] = '\0';
            str_len--;
        }

        takeid(room, line, str_len);
        takeletters(room, line, str_len);
        decript(room, strlen(room->letters));

        printf("Input: %s\n", line);
        printf("Letters: %s\n", room->letters);
        printf("ID: %ld\n", room->id);
        printf("DEC: %s\n", room->dec);
        fprintf(wfile, "%s\n", room->dec);

        freekeyvalue(room);
    }

    fclose(file);
    fclose(wfile);
    free(line);
    free(room);
    return 0;
}
