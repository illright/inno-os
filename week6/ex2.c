#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define LENGTH 128
#define READ_END 0
#define WRITE_END 1


int main() {
  int fd[2];
  pipe(fd);
  pid_t pid;

  if ((pid = fork()) > 0) {
    // Parent process
    char second[LENGTH];
    wait(NULL);  // Wait until the child terminates
    read(fd[READ_END], second, 10);
    close(fd[READ_END]);
    printf("%s\n", second);
  } else {
    // Child process
    char first[LENGTH] = "123456789";
    write(fd[WRITE_END], first, 10);
    close(fd[WRITE_END]);
  }
  return 0;
}
