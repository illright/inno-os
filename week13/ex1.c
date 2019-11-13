#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define PROCESS_COUNT 5
#define RESOURCE_COUNT 3


bool enoughResources(int request[RESOURCE_COUNT], int resources[RESOURCE_COUNT]) {
  for (int i = 0; i < RESOURCE_COUNT; ++i) {
    if (request[i] > resources[i]) {
      return false;
    }
  }
  return true;
}


int main() {
  int existingResources[RESOURCE_COUNT];
  int availableResources[RESOURCE_COUNT];
  int allocMatrix[PROCESS_COUNT][RESOURCE_COUNT];
  int requestMatrix[PROCESS_COUNT][RESOURCE_COUNT];

  FILE *input = fopen("input.txt", "r");
  if (input == NULL) {
    fprintf(stderr, "No file input.txt\n");
    return 1;
  }

  for (int i = 0; i < RESOURCE_COUNT; ++i) {
    fscanf(input, "%d", &existingResources[i]);
  }

  for (int i = 0; i < RESOURCE_COUNT; ++i) {
    fscanf(input, "%d", &availableResources[i]);
  }

  for (int i = 0; i < PROCESS_COUNT; ++i) {
    for (int j = 0; j < RESOURCE_COUNT; ++j) {
      fscanf(input, "%d", &allocMatrix[i][j]);
    }
  }

  for (int i = 0; i < PROCESS_COUNT; ++i) {
    for (int j = 0; j < RESOURCE_COUNT; ++j) {
      fscanf(input, "%d", &requestMatrix[i][j]);
    }
  }

  fclose(input);

  bool procFinished[PROCESS_COUNT];
  bool terminating = true;
  while (terminating) {
    terminating = false;
    for (int i = 0; i < PROCESS_COUNT; ++i) {
      if (!procFinished[i] && enoughResources(requestMatrix[i], availableResources)) {
        for (int j = 0; j < RESOURCE_COUNT; ++j) {
          availableResources[j] += allocMatrix[i][j];
        }
        procFinished[i] = true;
        terminating = true;
      }
    }
  }

  FILE *output = fopen("output.txt", "w");
  bool deadlocked = false;
  for (int i = 0; i < PROCESS_COUNT; ++i) {
    if (!procFinished[i]) {
      deadlocked = true;
      fprintf(output, "Process %d deadlocked.\n", i);
    }
  }

  if (!deadlocked) {
    fprintf(output, "No deadlock detected.\n");
  }

  fclose(output);

  return 0;
}
