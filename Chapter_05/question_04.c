#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
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
        printf("[PID %d] I am Child\n", (int) getpid());

        // execl("/bin/ls", "ls", "-l", NULL);
        
        char *args[] = {"ls", "-l", NULL};
        execv("/bin/ls", args);
    }
    else
    {
        // Parent Process
        printf("[PID %d] I am Parent\n", (int) getpid());
    }

    return 0;
}