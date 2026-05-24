#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/errno.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <inttypes.h>

#define NUM_ITER 1e6

int64_t get_total_nanoseconds(struct timespec ts) {
    return (int64_t)ts.tv_sec * 1000000000LL + (int64_t)ts.tv_nsec;
}

int main()
{
    cpu_set_t mask;
    int target_cpu = 0;

    CPU_ZERO(&mask);
    CPU_SET(target_cpu, &mask);

    if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {
        fprintf(stderr, "Error on sched_setaffinity: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("Affinity set to CPU %d\n", target_cpu);

    int pfd_0[2];
    int pfd_1[2];

    if (pipe(pfd_0) == -1)
    {
        fprintf(stderr, "Error on pipe 0: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    if (pipe(pfd_1) == -1)
    {
        fprintf(stderr, "Error on pipe 1: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char msg = 'x';
    char buf;

    pid_t fork_pid = fork();

    if (fork_pid == -1)
    {
        fprintf(stderr, "Error on fork: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if (fork_pid == 0)
    {
        close(pfd_0[1]);
        close(pfd_1[0]);

        for (int i = 0; i < NUM_ITER; ++i)
        {
            read(pfd_0[0], &buf, 1);
            write(pfd_1[1], &msg, 1);
        }

        close(pfd_0[0]);
        close(pfd_1[1]);

        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pfd_0[0]);
        close(pfd_1[1]);

        struct timespec start, end;
        int64_t elapsed_time_syscall;

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < NUM_ITER; ++i)
        {
            write(pfd_0[1], &msg, 1);
            read(pfd_1[0], &buf, 1);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed_time_syscall = get_total_nanoseconds(end) - get_total_nanoseconds(start);
        elapsed_time_syscall /= NUM_ITER;

        wait(NULL);

        close(pfd_0[1]);
        close(pfd_1[0]);

        printf("Elapset time: %" PRId64 " nanoseconds\n", elapsed_time_syscall);
    }


    return 0;
}