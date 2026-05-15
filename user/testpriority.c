#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid;

  printf("Priority scheduler test started\n");

  for(int i = 0; i < 5; i++){
    pid = fork();

    if(pid < 0){
      printf("fork failed\n");
      exit(1);
    }

    if(pid == 0){
      printf("Child %d started, pid=%d\n", i, getpid());

      for(volatile int j = 0; j < 100000000; j++){
        if(j % 20000000 == 0){
          printf("Child %d pid=%d running\n", i, getpid());
        }
      }

      printf("Child %d pid=%d finished\n", i, getpid());
      exit(0);
    }
  }

  for(int i = 0; i < 5; i++){
    wait(0);
  }

  printf("Priority scheduler test finished\n");
  exit(0);
}
