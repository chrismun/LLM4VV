#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a parallel region with 4 gangs
    #pragma acc parallel num_gangs(4)
    {
        // Create a loop with the gang clause
        #pragma acc loop gang
        for (int i = 0; i < 10; i++) {
            // Do something
        }
    }

    // Check that the loop was executed in parallel
    if (acc_get_num_gangs() != 4) {
        err = 1;
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