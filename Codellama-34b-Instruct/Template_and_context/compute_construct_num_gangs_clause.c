#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a parallel region with 2 gangs along dimension 1
    #pragma acc parallel num_gangs(2)
    {
        // Do some work here
    }

    // Create a kernels region with 4 gangs
    #pragma acc kernels num_gangs(4)
    {
        // Do some work here
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}