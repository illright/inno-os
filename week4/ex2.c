#include <stdio.h>
#include <unistd.h>


int main() {
  int pid;
  for (int i = 0; i < 5; ++i) {
    fork();
    sleep(5);
  }
  return 0;
}
