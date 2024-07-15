#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define NUM_REGISTERS 4

enum { A, B, C, D };

int registers[NUM_REGISTERS];

// Function to get the value from a register or immediate value
int get_value(const char *arg) {
    if (isalpha(arg[0])) {
        return registers[arg[0] - 'a'];
    } else {
        return atoi(arg);
    }
}

void execute_program(char **instructions, int num_instructions) {
    int pc = 0;

    while (pc >= 0 && pc < num_instructions) {
        char *line = instructions[pc];
        char op[4];
        char arg1[4];
        char arg2[4];

        sscanf(line, "%3s %3s %3s", op, arg1, arg2);

        if (strcmp(op, "cpy") == 0) {
            registers[arg2[0] - 'a'] = get_value(arg1);
        } else if (strcmp(op, "inc") == 0) {
            registers[arg1[0] - 'a']++;
        } else if (strcmp(op, "dec") == 0) {
            registers[arg1[0] - 'a']--;
        } else if (strcmp(op, "jnz") == 0) {
            if (get_value(arg1) != 0) {
                pc += get_value(arg2) - 1;
            }
        } else if (strcmp(op, "tgl") == 0) {
            int tgt = pc + get_value(arg1);
            if (tgt >= 0 && tgt < num_instructions) {
                char tgt_op[4];
                char tgt_arg1[4];
                char tgt_arg2[4];
                sscanf(instructions[tgt], "%3s %3s %3s", tgt_op, tgt_arg1, tgt_arg2);

                if (strcmp(tgt_op, "cpy") == 0) {
                    sprintf(instructions[tgt], "jnz %s %s", tgt_arg1, tgt_arg2);
                } else if (strcmp(tgt_op, "inc") == 0) {
                    sprintf(instructions[tgt], "dec %s", tgt_arg1);
                } else if (strcmp(tgt_op, "dec") == 0) {
                    sprintf(instructions[tgt], "inc %s", tgt_arg1);
                } else if (strcmp(tgt_op, "jnz") == 0) {
                    sprintf(instructions[tgt], "cpy %s %s", tgt_arg1, tgt_arg2);
                } else if (strcmp(tgt_op, "tgl") == 0) {
                    sprintf(instructions[tgt], "nop %s", tgt_arg1);
                } else if (strcmp(tgt_op, "nop") == 0) {
                    sprintf(instructions[tgt], "tgl %s", tgt_arg1);
                }
            }
        } else if (strcmp(op, "nop") == 0) {
        }

        pc++;
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Failed to open input.txt");
        return 1;
    }

    char *instructions[1000];
    int num_instructions = 0;
    char line[100];

    while (fgets(line, sizeof(line), file)) {
        instructions[num_instructions] = strdup(line);
        num_instructions++;
    }

    fclose(file);

    memset(registers, 0, sizeof(registers));
    registers[A] = 12; 

    execute_program(instructions, num_instructions);

    printf("%d\n", registers[A]);

    for (int i = 0; i < num_instructions; i++) {
        free(instructions[i]);
    }

    return 0;
}
