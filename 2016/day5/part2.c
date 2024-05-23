#include <openssl/md5.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool check_zero(char *str) {
  if (strlen(str) < 6) {
    return false;
  }
  for (size_t i = 0; i < 5; i++) {
    if (str[i] != '0') {
      return false;
    }
  }
  return true;
}

int main() {
  //char *mainstr = "abc";
   char *mainstr = "uqwqemis";
  long long ldex = 0;
  int resi = 0;
  char ress[9] = {0};
  char indstr[4042];
  char catstr[4042];
  unsigned char digest[32];
  char md5string[65]; //+ null terminator

  while (1) {
    sprintf(indstr, "%lld", ldex);
    strcpy(catstr, mainstr);
    strcat(catstr, indstr);

    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, catstr, strlen(catstr));
    MD5_Final(digest, &context);

    for (int i = 0; i < 16; ++i) {
      sprintf(&md5string[i * 2], "%02x", (unsigned int)digest[i]);
    }
    md5string[32] = '\0';

    if (check_zero(md5string)) {
      printf("Found matching hash with ldex: %lld\n", ldex);
      printf("%s\n", md5string);
      if (md5string[5] >= '0' && md5string[5] < '8') {
        printf("VALID\n");
         int index = md5string[5] - '0'; 
        if (ress[index] == 0) { 
          ress[index] = md5string[6];
          resi++;
        }
      }
      if (resi == 8) {
        ress[8] = '\0';
        printf("%s\n", ress);
        break;
      }
    }
    ldex++;
  }
  return 0;
}