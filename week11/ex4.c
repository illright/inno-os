#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
  int in = open("ex1.txt", O_RDONLY);
  int out = open("ex1.memcpy.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

  if (in == -1 || out == 1) {
    printf("Failed to open `ex1.txt` for reading or `ex1.memcpy.txt` for writing\n");
    return 1;
  }

  struct stat fst;
  if (fstat(in, &fst) == -1) {
    printf("Failed to get file stat\n");
    return 1;
  }

  if (fst.st_size == 0) {
    return 0;
  }
  ftruncate(out, fst.st_size);

  char* src = mmap(NULL, fst.st_size, PROT_READ, MAP_PRIVATE, in, 0);
  char* dst = mmap(NULL, fst.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, out, 0);
  if (src == MAP_FAILED || dst == MAP_FAILED) {
    printf("Failed to create an mmap\n");
    return 1;
  }

  memcpy(dst, src, fst.st_size);

  close(in);
  close(out);
}
