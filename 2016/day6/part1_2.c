#include <stdio.h>
#include <string.h>

//macro
//#define TEST
//#define MOST
#define LESS

// test 6
// input 8
#ifndef TEST
#define wordlen 8
#endif
#ifdef TEST
#define wordlen 6
#endif
// test 15
// input 623
#ifndef TEST
#define LISTLEN 623+1
#endif
#ifdef TEST
#define LISTLEN 15+1
#endif

#define MAX_LINE_LENGTH 1024

char least_frequent_char(unsigned char s[LISTLEN]) {
  int frequency[1024] = {0};
  int min_count = LISTLEN + 1;
  char min_char = '\0';

  for (int i = 0; i < LISTLEN; i++) {
    frequency[(unsigned char)s[i]]++;
  }

  for (int i = 0; i < LISTLEN; i++) {
    if (frequency[(unsigned char)s[i]] > 0 && frequency[(unsigned char)s[i]] < min_count) {
      min_count = frequency[(unsigned char)s[i]];
      min_char = s[i];
    }
  }

  return min_char;
}

char most_frequent_char(unsigned char s[LISTLEN]) {
  int frequency[1024] = {0};
  int max_count = 0;
  char max_char = '\0';

  for (int i = 0; i< LISTLEN; i++) {
    frequency[(unsigned char)s[i]]++;

    if (frequency[(unsigned char)s[i]] > max_count) {
      max_count = frequency[(unsigned char)s[i]];
      max_char = s[i];
    }
  }
  return max_char;
}

int main() {
  FILE *rfile;
  FILE *file0;
  FILE *file1;
  FILE *file2;
  FILE *file3;
  FILE *file4;
  FILE *file5;
  #ifndef TEST
  FILE *file6;
  FILE *file7;
  #endif
  unsigned char bfile0[LISTLEN];
  unsigned char bfile1[LISTLEN];
  unsigned char bfile2[LISTLEN];
  unsigned char bfile3[LISTLEN];
  unsigned char bfile4[LISTLEN];
  unsigned char bfile5[LISTLEN];
  #ifndef TEST
  unsigned char bfile6[LISTLEN];
  unsigned char bfile7[LISTLEN];
  #endif
  char line[MAX_LINE_LENGTH];

  rfile = fopen(
    #ifndef TEST
     "input.txt"
     #endif
     #ifdef TEST
     "test.txt"
     #endif
    , "r");
  if (rfile == NULL) {
    perror("Error opening test.txt");
    return 1;
  }

  file0 = fopen("0.txt", "w");
  file1 = fopen("1.txt", "w");
  file2 = fopen("2.txt", "w");
  file3 = fopen("3.txt", "w");
  file4 = fopen("4.txt", "w");
  file5 = fopen("5.txt", "w");
  #ifndef TEST
  file6 = fopen("6.txt", "w");
  file7 = fopen("7.txt", "w");
  #endif

  if (!file0 || !file1 || !file2 || !file3 || !file4 || !file5
  #ifndef TEST
   || !file6 ||
      !file7
    #endif
    ) {
    perror("Error opening one of the output files");
    return 1;
  }

  while (fgets(line, MAX_LINE_LENGTH, rfile) != NULL) {
    if (strlen(line) >= wordlen) {
      fprintf(file0, "%c", line[0]);
      fprintf(file1, "%c", line[1]);
      fprintf(file2, "%c", line[2]);
      fprintf(file3, "%c", line[3]);
      fprintf(file4, "%c", line[4]);
      fprintf(file5, "%c", line[5]);
      #ifndef TEST
      fprintf(file6, "%c", line[6]);
      fprintf(file7, "%c", line[7]);
      #endif
    }
  }
  fclose(rfile);
  fclose(file0);
  fclose(file1);
  fclose(file2);
  fclose(file3);
  fclose(file4);
  fclose(file5);
  #ifndef TEST
  fclose(file6);
  fclose(file7);
  #endif

  file0 = fopen("0.txt", "r");
  file1 = fopen("1.txt", "r");
  file2 = fopen("2.txt", "r");
  file3 = fopen("3.txt", "r");
  file4 = fopen("4.txt", "r");
  file5 = fopen("5.txt", "r");
  #ifndef TEST
  file6 = fopen("6.txt", "r");
  file7 = fopen("7.txt", "r");
  #endif

  if (!file0 || !file1 || !file2 || !file3 || !file4 || !file5
  #ifndef TEST
   || !file6 ||
      !file7
      #endif
      ) {
    perror("Error reopening one of the output files for reading");
    return 1;
  }

  fread(bfile0, sizeof(*bfile0), LISTLEN, file0);
  fread(bfile1, sizeof(*bfile1), LISTLEN, file1);
  fread(bfile2, sizeof(*bfile2), LISTLEN, file2);
  fread(bfile3, sizeof(*bfile3), LISTLEN, file3);
  fread(bfile4, sizeof(*bfile4), LISTLEN, file4);
  fread(bfile5, sizeof(*bfile5), LISTLEN, file5);
  #ifndef TEST
  fread(bfile6, sizeof(*bfile6), LISTLEN, file6);
  fread(bfile7, sizeof(*bfile7), LISTLEN, file7);
  #endif

  fclose(file0);
  fclose(file1);
  fclose(file2);
  fclose(file3);
  fclose(file4);
  fclose(file5);
  #ifndef TEST
  fclose(file6);
  fclose(file7);
  #endif

  #ifdef MOST
  printf("%c", most_frequent_char(bfile0));
  printf("%c", most_frequent_char(bfile1));
  printf("%c", most_frequent_char(bfile2));
  printf("%c", most_frequent_char(bfile3));
  printf( "%c", most_frequent_char(bfile4));
  printf( "%c", most_frequent_char(bfile5));
  #ifndef TEST
  printf( "%c", most_frequent_char(bfile6));
  printf( "%c", most_frequent_char(bfile7));
  #endif
  #endif

  #ifdef LESS
  printf("%c", least_frequent_char(bfile0));
  printf("%c", least_frequent_char(bfile1));
  printf("%c", least_frequent_char(bfile2));
  printf("%c", least_frequent_char(bfile3));
  printf( "%c", least_frequent_char(bfile4));
  printf( "%c", least_frequent_char(bfile5));
  #ifndef TEST
  printf( "%c", least_frequent_char(bfile6));
  printf( "%c", least_frequent_char(bfile7));
  #endif
  #endif

  return 0;
}