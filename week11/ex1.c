#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
  int fd = open("ex1.txt", O_RDWR);
  if (fd == -1) {
    printf("Couldn't open `ex1.txt`\n");
    return 1;
  }

  struct stat fst;
  if (fstat(fd, &fst) == -1) {
    printf("Failed to get file stat\n");
    return 1;
  }

  char* map = mmap(NULL, fst.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (map == MAP_FAILED) {
    printf("Failed to create an mmap\n");
    return 1;
  }

  ftruncate(fd, 18);
  memcpy(map, "This is a nice day", 18 + 1);

  close(fd);
  return 0;
}
