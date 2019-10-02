#include <stdio.h>
#include <stdlib.h>


int main() {
  printf("Please, enter a number: ");
  int n;
  scanf("%d", &n);

  int *array = calloc(n, sizeof(int));
  for (int i = 0; i < n; ++i) {
    array[i] = i;
  }

  for (int i = 0; i < n; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");

  free(array);
  return 0;
}
