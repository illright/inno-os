#include <stdio.h>
#include <string.h>
#define MAX_STRLEN 65536

int main() {
  printf("Please, enter a string: ");
  char string[MAX_STRLEN];
  fgets(string, MAX_STRLEN, stdin);

  for (int i = strlen(string) - 2; i >= 0; --i) {
    putchar(string[i]);
  }
  putchar('\n');
  return 0;
}
