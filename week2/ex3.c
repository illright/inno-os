#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "The program must be passed exactly one integer parameter.\n");
    return -1;
  }

  int n;
  sscanf(argv[1], "%d", &n);

  int width = 2 * n - 1;
  for (int stars = 1; stars <= n; ++stars) {
    int spaces = (width - 2 * stars + 1) / 2;
    for (int j = 0; j < spaces; ++j) {
      putchar(' ');
    }

    for (int j = 0; j < 2 * stars - 1; ++j) {
      putchar('*');
    }

    for (int j = 0; j < spaces; ++j) {
      putchar(' ');
    }

    putchar('\n');
  }

  return 0;
}
