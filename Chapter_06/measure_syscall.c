#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <wait.h>
#include <sys/syscall.h>

#define NUM_ITER 1e6

int64_t get_total_nanoseconds(struct timespec ts) {
    return (int64_t)ts.tv_sec * 1000000000LL + (int64_t)ts.tv_nsec;
}

int main()
{
    struct timespec start, end;
    int64_t elapsed_time_syscall;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < NUM_ITER; ++i)
    {
        read(STDOUT_FILENO, "", 0);
        // wait(NULL);
        // syscall(SYS_gettid);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed_time_syscall = get_total_nanoseconds(end) - get_total_nanoseconds(start);
    elapsed_time_syscall /= NUM_ITER;

    printf("Elapsed time (avg - single syscall): %" PRId64 " nanoseconds\n", elapsed_time_syscall);

    return 0;
}