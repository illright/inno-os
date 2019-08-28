#include <stdio.h>

int swap(int *a, int *b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

int main() {
  printf("Please, enter two integers, space-separated: ");
  int a, b;
  scanf("%d %d", &a, &b);
  swap(&a, &b);

  printf("%d %d\n", a, b);
  return 0;
}
