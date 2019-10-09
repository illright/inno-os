#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MB 1024 * 1024


int main() {
  void* mem;
  for (int i = 0; i < 10; ++i) {
    mem = malloc(10 * MB);
    memset(mem, 0, 10 * MB);
    sleep(1);
  }
}
