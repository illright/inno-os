#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#define MB 1024 * 1024


int main() {
  void* mem;
  struct rusage usage;
  for (int i = 0; i < 10; ++i) {
    mem = malloc(10 * MB);
    memset(mem, 0, 10 * MB);
    getrusage(RUSAGE_SELF, &usage);

    printf("----------------\n");
    printf("User CPU time:\t%ld.%06ld\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("System CPU time:\t%ld.%06ld\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    printf("Maximum resident set size:\t%ld\n", usage.ru_maxrss);
    printf("Page reclaims (soft page faults):\t%ld\n", usage.ru_minflt);
    printf("Page faults (hard page faults):\t%ld\n", usage.ru_majflt);
    printf("Block input operations:\t%ld\n", usage.ru_inblock);
    printf("Block output operations:\t%ld\n", usage.ru_oublock);
    printf("Voluntary context switches:\t%ld\n", usage.ru_nvcsw);
    printf("Involuntary context switches:\t%ld\n", usage.ru_nivcsw);

    sleep(1);
  }

  return 0;
}
