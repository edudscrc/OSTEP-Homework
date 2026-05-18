#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("file_q03.txt", O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        // Error
        fprintf(stderr, "Error on open.\n");
        exit(1);
    }
    close(fd);

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
        printf("[PID %d] hello\n", (int) getpid());

        int fd = open("file_q03.txt", O_WRONLY);
        if (fd == -1)
        {
            // Error
            fprintf(stderr, "[Child] Error on open.\n");
            exit(1);
        }

        const char *msg = "done";
        write(fd, msg, strlen(msg));
        close(fd);
    }
    else
    {
        // Parent Process
        int fd = open("file_q03.txt", O_RDONLY);
        if (fd == -1)
        {
            // Error
            fprintf(stderr, "[Parent] Error on open.\n");
            exit(1);
        }
        int child_done = 0;
        char buf[4];
        while (!child_done)
        {
            ssize_t c = read(fd, buf, 4);
            if (memcmp(buf, "done", 4) == 0)
            {
                child_done = 1;
            }
        }
        close(fd);
        printf("[PID %d] goodbye\n", (int) getpid());
    }

    return 0;
}