#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_PAGES 1000
#define AGE_LIMIT 28


int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "The program should have exactly one parameter: the number of page frames.\n");
    return 1;
  }

  int pageFrames;
  sscanf(argv[1], "%d", &pageFrames);

  int *memory = calloc(pageFrames, sizeof(int));
  int *refCount = calloc(MAX_PAGES, sizeof(int));
  int hits = 0;
  int misses = 0;

  FILE* pageReferences = fopen("input_improved.txt", "r");
  int reference;
  while (!feof(pageReferences)) {
    if (fscanf(pageReferences, "%d", &reference) != 1) {
      break;
    }

    // printf("Referencing frame %d\n", reference);

    bool frameFound = false;
    for (int frameIdx = 0; frameIdx < pageFrames; ++frameIdx) {
      if (reference == memory[frameIdx]) {
        hits++;
        frameFound = true;
        break;
      }
    }

    if (!frameFound) {
      misses++;

      int oldestFrameIdx = 0;
      int leastCounter = refCount[memory[oldestFrameIdx]];
      for (int frameIdx = 1; frameIdx < pageFrames; ++frameIdx) {
        if (leastCounter > refCount[memory[frameIdx]]) {
          oldestFrameIdx = frameIdx;
          leastCounter = refCount[memory[frameIdx]];
        }
      }
      memory[oldestFrameIdx] = reference;
    }

    for (int i = 0; i < MAX_PAGES; ++i) {
      refCount[i] >>= 1;
      refCount[i] |= (reference == i) << AGE_LIMIT;
    }

    // printf("Memory state: [");
    // for (int frameIdx = 0; frameIdx < pageFrames; ++frameIdx) {
    //   printf("%d, ", memory[frameIdx]);
    // }
    // printf("]\n");
    // printf("refCounts state: [");
    // for (int i = 0; i < MAX_PAGES; ++i) {
    //   printf("%d, ", refCount[i]);
    // }
    // printf("]\n\n");
  }

  printf("Hits:\t%d\n", hits);
  printf("Misses:\t%d\n", misses);
  printf("Hit/miss ratio: %f\n", (float)hits / misses);

  free(memory);
  free(refCount);
  return 0;
}
