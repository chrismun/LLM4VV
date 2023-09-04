#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a parallel region with 4 workers
    #pragma acc parallel num_workers(4)
    {
        // Create a loop with the worker clause
        #pragma acc loop worker
        for (int i = 0; i < 10; i++) {
            // Do some work
            printf("Worker %d: iteration %d\n", acc_get_worker_id(), i);
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}