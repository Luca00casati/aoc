#include <stdio.h>
#include <string.h>

#define MAX_BOTS 1024
#define MAX_OUTPUTS 1024

typedef struct {
    int low_dest_type;
    int low_dest;
    int high_dest_type;
    int high_dest;
} BotInstructions;

typedef struct {
    int chips[2];
    int chip_count;
} Bot;

Bot bots[MAX_BOTS];
int outputs[MAX_OUTPUTS];
BotInstructions instructions[MAX_BOTS];

void process_instructions() {
    int i, low_value, high_value, low_dest, high_dest;

    int changed;
    do {
        changed = 0;
        for (i = 0; i < MAX_BOTS; i++) {
            if (bots[i].chip_count == 2) {
                low_value = (bots[i].chips[0] < bots[i].chips[1]) ? bots[i].chips[0] : bots[i].chips[1];
                high_value = (bots[i].chips[0] > bots[i].chips[1]) ? bots[i].chips[0] : bots[i].chips[1];

                if ((low_value == 17 && high_value == 61) || (low_value == 61 && high_value == 17)) {
                    printf("Bot responsible for comparing 17 and 61: %d\n", i);
                }

                low_dest = instructions[i].low_dest;
                if (instructions[i].low_dest_type == 0) {
                    bots[low_dest].chips[bots[low_dest].chip_count++] = low_value;
                } else {
                    outputs[low_dest] = low_value;
                }

                high_dest = instructions[i].high_dest;
                if (instructions[i].high_dest_type == 0) {
                    bots[high_dest].chips[bots[high_dest].chip_count++] = high_value;
                } else {
                    outputs[high_dest] = high_value;
                }

                bots[i].chip_count = 0;
                changed = 1;
            }
        }
    } while (changed);
}

int main() {
    char line[256];
    int value, bot, bot1, bot2;
    char dest1[10], dest2[10];
    FILE* file = fopen("input.txt", "r");
    if (file == NULL){
        fprintf(stderr, "file error\n");
        return 1;
    }
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "value %d goes to bot %d", &value, &bot) == 2) {
            bots[bot].chips[bots[bot].chip_count++] = value;
        } else if (sscanf(line, "bot %d gives low to %s %d and high to %s %d",
                          &bot, dest1, &bot1, dest2, &bot2) == 5) {
            instructions[bot].low_dest_type = strcmp(dest1, "bot") == 0 ? 0 : 1;
            instructions[bot].low_dest = bot1;
            instructions[bot].high_dest_type = strcmp(dest2, "bot") == 0 ? 0 : 1;
            instructions[bot].high_dest = bot2;
        }
    }

    process_instructions();

    for (int i = 0; i < MAX_OUTPUTS; i++) {
        if (outputs[i] != 0) {
            printf("Output %d: %d\n", i, outputs[i]);
        }
    }

    fclose(file);
    return 0;
}
// 23903
