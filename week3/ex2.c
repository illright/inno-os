#include <stdio.h>

void bubble_sort(int* array, int size) {
  int temp;
  for (int i = 0; i < size; ++i) {
    for (int j = i; j < size; ++j) {
      if (array[i] > array[j]) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
}


int main() {
  int array[5] = {3, 4, 1, 2, 5};
  bubble_sort(array, 5);
  for (int i = 0; i < 5; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
  return 0;
}
