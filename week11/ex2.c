#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
  putc('H', stdout);
  sleep(1);
  putc('e', stdout);
  sleep(1);
  putc('l', stdout);
  sleep(1);
  putc('l', stdout);
  sleep(1);
  putc('o', stdout);
  sleep(1);
  putc('\n', stdout);
  return 0;
}
