#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <wait.h>
#include <sys/syscall.h>

#define NUM_ITER 1e7

int64_t get_total_nanoseconds(struct timespec ts) {
    return (int64_t)ts.tv_sec * 1000000000LL + (int64_t)ts.tv_nsec;
}

int main()
{
    struct timespec start, end;
    int64_t elapsed_time = 0;

    for (int i = 0; i < NUM_ITER; ++i)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
    
        // My Machine:
        // read 0 bytes -> ~470 ns
        // wait (without any child) -> ~360 ns
        // calling SYS_gettid directly -> ~275 ns

        // read(STDOUT_FILENO, "", 0);
        // wait(NULL);
        syscall(SYS_gettid);
    
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed_time += get_total_nanoseconds(end) - get_total_nanoseconds(start);
    }

    printf("Elapsed time (all calls): %" PRId64 " nanoseconds\n", elapsed_time);

    elapsed_time /= NUM_ITER;

    printf("Elapsed time (avg - single syscall): %" PRId64 " nanoseconds\n", elapsed_time);

    return 0;
}