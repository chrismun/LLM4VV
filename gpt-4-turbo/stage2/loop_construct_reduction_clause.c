#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1: loop construct reduction clause, V:2.7-3.3
int test1() {
    int err = 0;
    const int N = 1000;
    int accumulator = 0;
    int *data = (int *)malloc(N * sizeof(int));

    // Initialize data to 1's
    for (int i = 0; i < N; ++i) {
        data[i] = 1;
    }

    #pragma acc parallel loop reduction(+:accumulator)
    for (int i = 0; i < N; ++i) {
        accumulator += data[i];
    }

    // Check if the reduction was correct
    if (accumulator != N) {
        err++;
    }

    free(data);

    return err;
}
#endif

int main() {
    const int NUM_TEST_CALLS = 10;
    int failcode = 0;
    int failed = 0;

    #ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    #endif

    return failcode;
}