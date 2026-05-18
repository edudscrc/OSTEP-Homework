#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int pfd[2];
    if (pipe(pfd) == -1)
    {
        fprintf(stderr, "Error on pipe: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    const char *msg = "Hello from c1!";
    // strlen doesn't count null termination
    const ssize_t len_msg = strlen(msg);

    int c1_pid = fork();
    if (c1_pid == -1)
    {
        fprintf(stderr, "Error on first fork: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if (c1_pid == 0)
    {
        close(pfd[0]);

        ssize_t write_bytes = write(pfd[1], msg, len_msg);
        if (write_bytes == -1)
        {
            fprintf(stderr, "Error on write: %s\n", strerror(errno));
            exit(1);
        }

        close(pfd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        int c2_pid = fork();
        if (c2_pid == -1)
        {
            fprintf(stderr, "Error on second fork: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        else if (c2_pid == 0)
        {
            close(pfd[1]);

            char buf[len_msg + 1];
            ssize_t read_bytes = read(pfd[0], buf, len_msg);
            if (read_bytes == -1)
            {
                fprintf(stderr, "Error on read: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            buf[read_bytes] = '\0';
            printf("[Child 2] I got a message from Child 1: %s\n", buf);

            close(pfd[0]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(pfd[0]);
            close(pfd[1]);
            waitpid(c1_pid, NULL, 0);
            waitpid(c2_pid, NULL, 0);
        }
    }

    return 0;
}