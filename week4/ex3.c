#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256


int main() {
  char command[MAX_LINE];
  while (1) {
    printf("> ");
    fgets(command, MAX_LINE, stdin);
    if (strcmp(command, "exit\n") == 0) {
      break;
    }

    system(command);
  }
}
