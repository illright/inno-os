#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define STDIN_FD 0
#define STDOUT_FD 1
#define BUF_SIZE 1024


bool exists(char* filename) {
  int testFd = open(filename, O_RDONLY);
  bool result = (testFd != -1);
  close(testFd);
  return result;
}


int main(int argc, char **argv) {
  bool appendMode;
  int fileStart = 1;

  if (argc > 1 && strcmp(argv[1], "-a") == 0) {
    appendMode = true;
    fileStart++;
  } else {
    appendMode = false;
  }

  int *fds = calloc(argc - fileStart + 1, sizeof(int));
  fds[0] = STDOUT_FD;

  for (int argi = fileStart, idx = 1; argi < argc; ++argi, ++idx) {
    if (appendMode && exists(argv[argi])) {
      fds[idx] = open(argv[argi], O_RDWR | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
    } else {
      fds[idx] = open(argv[argi], O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    }

    if (fds[idx] == -1) {
      printf("Couldn't open `%s`\n", argv[argi]);
      return 1;
    }
  }

  char buffer[BUF_SIZE];
  int numRead;
  while ((numRead = read(STDIN_FD, buffer, BUF_SIZE)) > 0) {
    for (int i = 0; i < argc - fileStart + 1; ++i) {
      write(fds[i], buffer, numRead);
    }
  }

  for (int i = 1; i < argc - fileStart + 1; ++i) {
    close(fds[i]);
  }

  free(fds);
  return 0;
}
