#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#define CAPACITY 5


bool isProducerSleeping;
bool isConsumerSleeping;

void sleep(bool* sleepStatus) {
  *sleepStatus = true;
}

void wakeup(bool* sleepStatus) {
  *sleepStatus = false;
}


int* buffer[CAPACITY];
int length = 0;

void *producer(void* vararg) {
  while (true) {
    if (!isProducerSleeping) {
      if (length == CAPACITY) {
        sleep(&isProducerSleeping);
        continue;
      }
      buffer[length] = malloc(sizeof(int));
      *(buffer[length]) = 1;
      if (length == 0) {
        wakeup(&isConsumerSleeping);
      }
      length++;
    }
  }
}


int main() {
  pthread_t producerID;
  pthread_create(&producerID, NULL, producer, NULL);

  while (true) {
    if (!isConsumerSleeping) {
      if (length == 0) {
        sleep(&isConsumerSleeping);
        continue;
      }
      *(buffer[length]) = 0;
      free(buffer[length]);
      if (length == CAPACITY) {
        wakeup(&isProducerSleeping);
      }
      length--;
    }
  }

  return 0;
}
