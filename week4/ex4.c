#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 256


int main() {
  char command[MAX_LINE];
  bool isBackground;
  while (1) {
    printf("> ");
    fgets(command, MAX_LINE, stdin);
    command[strlen(command) - 1] = 0;
    if (strcmp(command, "exit") == 0) {
      break;
    }

    pid_t pid;
    char* args[128];
    char* ptr = strtok(command, " ");
    int i = 0;
    while (ptr != NULL) {
      args[i++] = ptr;
      ptr = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (strcmp(args[i - 1], "&") == 0) {
      args[--i] = 0;
      isBackground = true;
    } else {
      isBackground = false;
    }

    if ((pid = fork()) == 0) {
      execve(args[0], args, NULL);
    } else {
      int status;
      if (!isBackground) {
        waitpid(pid, &status, 0);
      }
    }
  }
}
