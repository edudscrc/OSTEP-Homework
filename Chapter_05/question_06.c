#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

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

        // This gives an error.
        pid_t idk_pid = waitpid(-1, NULL, 0);
        if (idk_pid == -1)
        {
            fprintf(stderr, "[PID %d] Error on wait: %s\n", (int) getpid(), strerror(errno));
        }

        printf("[PID %d] I am done.\n", (int) getpid());
    }
    else
    {
        // Parent Process
        printf("[PID %d] I am Parent\n", (int) getpid());

        pid_t c_pid = waitpid(pid, NULL, 0);
        // pid_t c_pid = wait(NULL);
        if (c_pid == -1)
        {
            fprintf(stderr, "[PID %d] Error on wait: %s\n", (int) getpid(), strerror(errno));
        }

        printf("[PID %d] Child is done. I am done too.\n", (int) getpid());
    }

    return 0;
}