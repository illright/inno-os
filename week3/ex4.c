#include <stdio.h>
#define SIZE 5


void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int array[SIZE], int lo, int hi) {
	int pivot = array[hi];

	int i = lo - 1;
	for (int j = lo; j < hi; ++j) {
		if (array[j] < pivot) {
			++i;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[hi]);

	return i + 1;
}

void quick_sort(int array[SIZE], int lo, int hi) {
	if (lo < hi) {
		int point = partition(array, lo, hi);
		quick_sort(array, lo, point - 1);
		quick_sort(array, point + 1, hi);
	}
}


int main() {
	int array[SIZE] = {5, 3, 1, 2, 4};
	quick_sort(array, 0, SIZE - 1);

  for (int i = 0; i < SIZE; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
	return 0;
}
