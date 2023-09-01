#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc parallel num_gangs(1) num_workers(1)
    {
        #pragma acc loop
        for (int i = 0; i < 100; i++) {
            if (omp_get_thread_num() != 0) {
                err = 1;
            }
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc parallel num_gangs(1) num_workers(1)
    {
        #pragma acc loop
        for (int x = 0; x < NUM_TEST_CALLS; x++) {
            failed = failed + test1();
        }
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}