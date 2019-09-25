#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LENGTH 128
#define READ_END 0
#define WRITE_END 1


int main() {
  char first[LENGTH] = "This is a string\n";
  char second[LENGTH];

  int fd[2];
  pipe(fd);

  write(fd[WRITE_END], first, strlen(first) + 1);
  close(fd[WRITE_END]);

  read(fd[READ_END], second, strlen(first) + 1);
  close(fd[READ_END]);

  printf("%s", second);
  return 0;
}
