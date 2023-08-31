#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    int num_workers = omp_get_num_threads();
    if (num_workers != 4) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}