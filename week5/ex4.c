#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#define INIT_VECTOR_CAPACITY 8

// Exit the program with a failure exit code if the passed pointer is NULL.
void* failOnNull(void* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

typedef struct vector {
    void** array;
    int capacity;
    int size;
} vector;


// Create a vector with space for INIT_VECTOR_CAPACITY elements.
vector* mkVector() {
    void** array = failOnNull(calloc(INIT_VECTOR_CAPACITY, sizeof(void*)));
    vector* result = failOnNull(malloc(sizeof(vector)));

    result->array = array;
    result->capacity = INIT_VECTOR_CAPACITY;
    result->size = 0;
    return result;
}


// Destroy the vector, freeing the occupied memory.
void destroyVector(vector* vc) {
    if (vc == NULL) {
        return;
    }

    for (int i = 0; i < vc->size; ++i) {
        free(vc->array[i]);
    }
    free(vc->array);
    free(vc);
}


// Push the `element` to the end of the vector `vc`.
void append(vector* vc, void* element) {
    if (vc->size + 1 > vc->capacity) {
        vc->capacity *= 2;
        vc->array = failOnNull(realloc(vc->array, vc->capacity * sizeof(void*)));
    }

    vc->array[vc->size++] = element;
}


// Remove the last element from the vector `vc`.
void removeLast(vector* vc) {
    vc->size--;
}


vector* work;
int activeThreads, workingThreads;
pthread_mutex_t globMutex;

void *computer(void* vararg) {
  while (true) {
    int *a = NULL, *b = NULL;
    pthread_mutex_lock(&globMutex);
    if (work->size >= 2) {
      workingThreads++;
      a = work->array[work->size - 1];
      removeLast(work);
      b = work->array[work->size - 1];
      removeLast(work);
    }
    pthread_mutex_unlock(&globMutex);

    if (a == NULL || b == NULL) {
      if (workingThreads > 0) {
        continue;
      }
      activeThreads--;
      return NULL;
    }

    int max;
    if (*a > *b) {
      max = *a;
    } else {
      max = *b;
    }

    while (max <= (*a) * (*b)) {
      if (max % *a == 0 && max % *b == 0) {
        break;
      }
      max++;
    }
    pthread_mutex_lock(&globMutex);
    workingThreads--;
    int* newMax = malloc(sizeof(int));
    *newMax = max;
    free(a);
    free(b);
    append(work, newMax);
    pthread_mutex_unlock(&globMutex);
  }
}


int main(int argc, char** argv) {
  if (argc != 3) {
    printf("The program should be given exactly 2 arguments.\n");
    return 1;
  }

  work = mkVector();
  pthread_mutex_init(&globMutex, NULL);

  FILE* input = fopen(argv[1], "r");
  int* number;
  while (!feof(input)) {
    number = malloc(sizeof(int));
    fscanf(input, "%d", number);
    if (*number != 0) {
      append(work, number);
    }
  }

  int threadAmt = atoi(argv[2]);
  activeThreads = threadAmt;
  workingThreads = 0;
  pthread_t* threadIDs = calloc(threadAmt, sizeof(pthread_t));
  for (int i = 0; i < threadAmt; ++i) {
    pthread_create(&(threadIDs[i]), NULL, computer, NULL);
  }

  while (activeThreads != 0) {
    sleep(1);
  }

  printf("LCM: %d\n", *(int*)(work->array[0]));

  destroyVector(work);
  return 0;
}
