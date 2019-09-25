#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


#define READ_END 0
#define WRITE_END 1


int main() {
  pid_t pid1;
  pid_t pid2;
  int fd[2];
  pipe(fd);

  if (pid1 = fork()) {
    // Parent process
    printf("Parent: forked out 1st child %d\n", pid1);
    close(fd[READ_END]);

    if (pid2 = fork()) {
      // Still parent process
      printf("Parent: forked out 2nd child %d\n", pid2);
      char pid1_str[64];
      sprintf(pid1_str, "%d", pid2);
      write(fd[WRITE_END], pid1_str, 64);
      printf("Parent: written the PID of the 2nd child\n");
      close(fd[WRITE_END]);

      int pid2_status;
      waitpid(pid2, &pid2_status, 0);
      printf("Parent: 2nd child changed status to %d\n", pid2_status);
      printf("Parent: terminating 1st child\n");
      kill(pid1, SIGTERM);
      printf("Parent: terminating 2nd child\n");
      kill(pid2, SIGTERM);
      printf("Parent: exiting\n");
    } else {
      // 2nd child
      while (1) {
        printf("2nd child: I'm alive\n");
        sleep(1);
      }
    }
  } else {
    // 1st child
    char sibling_str[64];
    pid_t sibling;
    close(fd[WRITE_END]);

    read(fd[READ_END], sibling_str, 64);
    printf("1st child: read the PID of the 2nd child\n");
    close(fd[READ_END]);
    sibling = atoi(sibling_str);
    printf("1st child: PID of the 2nd child is %d\n", sibling);

    sleep(2);
    printf("1st child: SIGSTOPping the 2nd child\n");
    kill(sibling, SIGSTOP);
    printf("1st child: SIGTERMing the 2nd child\n");
    kill(sibling, SIGTERM);

    while (1) {}
  }

  return 0;
}
