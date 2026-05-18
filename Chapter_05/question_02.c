#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("file_q02.txt", O_CREAT | O_RDWR | O_TRUNC);
    if (fd == -1)
    {
        // Error
        fprintf(stderr, "Error on open.\n");
        exit(1);
    }

    printf("File opened with descriptor: %d\n", fd);

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
        printf("[PID %d] I am Child.\n", (int) getpid());

        const char *msg = "Hello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\nHello from Child.\n";
        write(fd, msg, strlen(msg));
    }
    else
    {
        // Parent Process
        printf("[PID %d] I am Parent.\n", (int) getpid());

        const char *msg = "Hello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\nHello from Parent.\n";
        write(fd, msg, strlen(msg));

        close(fd);
    }

    return 0;
}