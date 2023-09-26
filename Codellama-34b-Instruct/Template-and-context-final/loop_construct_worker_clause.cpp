#include <iostream>
#include <cstdlib>
#include <cmath>
#include <acc/acc.h>

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
        for (int i = 0; i < 100; i++) {
            // Do some work
            int x = rand() % 100;
            int y = rand() % 100;
            int z = x + y;
            #pragma acc atomic update
            z += 1;
        }
    }

    // Check that all workers completed execution of their assigned iterations
    #pragma acc parallel num_workers(4)
    {
        int i = 0;
        #pragma acc loop worker
        for (int j = 0; j < 100; j++) {
            if (i != j) {
                err = 1;
                break;
            }
            i++;
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