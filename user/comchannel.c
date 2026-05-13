#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
    int p[2];
    char buf[100];

    if (pipe(p) < 0) {
        printf("pipe failed\n");
        exit(1);
    }

    int pid = fork();

    if (pid < 0) {
        printf("fork failed\n");
        exit(1);
    }

    if (pid == 0) {
        // Child process (reader)
        close(p[1]);
        read(p[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
        close(p[0]);
    } else {
        // Parent process (writer)
        close(p[0]);
        write(p[1], "Hello from parent via pipe!", 28);
        close(p[1]);
        wait(0);
    }

    exit(0);
}
