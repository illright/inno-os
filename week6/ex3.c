#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int signal_count = 0;

void notify_int(int sig) {
  if (signal_count++ == 0) {
    printf(" Interrupt received. Send again to kill the program.\n");
  } else {
    exit(0);
  }
}

int main() {
  signal(SIGINT, notify_int);
  while (1) {}
  return 0;
}
