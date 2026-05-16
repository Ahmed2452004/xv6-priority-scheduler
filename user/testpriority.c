#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
busy_work(void)
{
  volatile unsigned long long counter = 0;

  for(unsigned long long i = 0; i < 500000000ULL; i++){
    counter++;
  }
}

int
main(int argc, char *argv[])
{
  int pid;
  int priorities[5] = {1, 2, 3, 4, 5};

  printf("\n=== Priority Scheduler Test ===\n");
  printf("Lower number means higher priority\n");
  printf("Each child gets a different priority and performs CPU-bound work.\n\n");

  for(int i = 0; i < 5; i++){
    pid = fork();

    if(pid < 0){
      printf("fork failed\n");
      exit(1);
    }

    if(pid == 0){
      int priority = priorities[i];

      setpriority(getpid(), priority);

      printf("START  child=%d pid=%d priority=%d\n", i, getpid(), priority);

      busy_work();

      printf("FINISH child=%d pid=%d priority=%d\n", i, getpid(), priority);
      exit(0);
    }
  }

  for(int i = 0; i < 5; i++){
    wait(0);
  }

  printf("\n=== Test Finished ===\n");
  printf("Expected: higher-priority children should finish earlier.\n");
  printf("Aging/fairness should prevent low-priority children from starving.\n");

  exit(0);
}
