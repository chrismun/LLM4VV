#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc parallel num_workers(4)
    {
        #pragma acc loop worker
        for (int i = 0; i < 100; i++) {
            // Do some work
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc parallel num_workers(4)
    {
        #pragma acc loop worker
        for (int x = 0; x < NUM_TEST_CALLS; x++) {
            failed = test1();
            if (failed != 0) {
                failcode = failcode + (1 << x);
            }
        }
    }

    return failcode;
}