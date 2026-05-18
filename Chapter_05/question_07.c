#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
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

        close(STDOUT_FILENO);
        int fd = open("file_q07.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

        printf("[PID %d] I have closed standard output.\n", (int) getpid());
        close(fd);
    }
    else
    {
        // Parent Process
        printf("[PID %d] I am Parent\n", (int) getpid());
    }

    return 0;
}