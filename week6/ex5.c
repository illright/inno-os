#include <stdio.h>
#include <signal.h>
#include <unistd.h>


int main() {
  pid_t pid;

  if (pid = fork()) {
    // Parent process
    sleep(10);
    kill(pid, SIGTERM);
  } else {
    while (1) {
      printf("I'm alive\n");
      sleep(1);
    }
  }

  return 0;
}
