#include <stdio.h>
#define SYM_COUNT 20


int main() {
  FILE *devRandom = fopen("/dev/random", "rb");
  char string[21];
  fread(string, sizeof(char), SYM_COUNT, devRandom);
  string[20] = '\0';
  printf("%s", string);
  return 0;
}
