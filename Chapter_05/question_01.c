#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int x = 100;

    int pid = fork();

    if (pid == -1)
    {
        // Error
        fprintf(stderr, "Error on fork.\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child Process
        x = 101;
        printf("[PID %d] I am Child. x = %d\n", (int) getpid(), x);
    }
    else
    {
        // Parent Process
        x = 102;
        printf("[PID %d] I am Parent. x = %d\n", (int) getpid(), x);
    }

    return 0;
}