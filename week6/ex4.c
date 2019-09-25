#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


void handle_kill(int sig) {
  printf("Pls no :c\n");
  exit(1);
}

void handle_stop(int sig) {
  printf("Okay I'll stop\n");
}

void handle_usr1(int sig) {
  printf("Hi, friend!\n");
}

int main() {
  signal(SIGKILL, handle_kill);
  signal(SIGSTOP, handle_stop);
  signal(SIGUSR1, handle_usr1);
  while (1) {}
  return 0;
}
