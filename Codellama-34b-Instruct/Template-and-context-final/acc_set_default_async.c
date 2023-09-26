#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Set the default asynchronous activity queue to a random value
    int async_arg = rand() % 100;
    acc_set_default_async(async_arg);

    // Create a compute construct with an async clause
    #pragma acc parallel async
    {
        // Do some work
    }

    // Check that the default asynchronous activity queue was used
    if (acc_get_default_async() != async_arg) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}