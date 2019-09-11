#include <stdio.h>
#include <unistd.h>


int main() {
  int n;
  if (n = fork()) {
    printf("Hello from child [PID - %d]\n", n);
  } else {
    printf("Hello from parent [PID - %d]\n", n);
  }
  return 1;
}
