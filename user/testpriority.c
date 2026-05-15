#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid;
  int priorities[5] = {1, 2, 3, 4, 5};

  printf("Priority scheduler test started\n");

  for(int i = 0; i < 5; i++){
    pid = fork();

    if(pid < 0){
      printf("fork failed\n");
      exit(1);
    }

    if(pid == 0){
      setpriority(getpid(), priorities[i]);

      printf("Child %d started pid=%d priority=%d\n", i, getpid(), priorities[i]);

      for(volatile int j = 0; j < 100000000; j++){
        if(j % 20000000 == 0){
          printf("Child %d pid=%d priority=%d running\n", i, getpid(), priorities[i]);
        }
      }

      printf("Child %d finished pid=%d priority=%d\n", i, getpid(), priorities[i]);
      exit(0);
    }
  }

  for(int i = 0; i < 5; i++){
    wait(0);
  }

  printf("Priority scheduler test finished\n");
  exit(0);
}
