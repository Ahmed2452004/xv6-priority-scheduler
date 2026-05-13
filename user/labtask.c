#include "kernel/types.h"
#include "user/user.h"

int main() {
    int pid = fork();

    if (pid < 0) {
        printf("Error: fork failed\n");
        exit(1);
    }

    else if (pid == 0) {
        // Child process
        printf("Child: running ls...\n");

        char *args[] = {"ls", 0};
        exec("ls", args);

        // If exec fails
        printf("Error: exec failed\n");
        exit(1);
    }

    else {
        // Parent process
        printf("Parent: waiting...\n");

        wait(0);

        printf("Parent: child finished\n");
    }

    exit(0);
}
