#include <stdio.h>
#include <pthread.h>
#define N 5


void *callable(void* vararg) {
  printf("thread ID: %lu, some text\n", pthread_self());
  return NULL;
}


int main() {
  pthread_t threads[N];
  for (int i = 0; i < N; ++i) {
    pthread_create(&(threads[i]), NULL, callable, NULL);
    printf("created thread %lu\n", threads[i]);
    pthread_join(threads[i], NULL);
  }

  return 0;
}
