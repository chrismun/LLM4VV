#include <stdlib.h>
#include <stdio.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Create an array of async-arguments
    int wait_arg[NUM_TEST_CALLS];
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        wait_arg[i] = rand() % 2;
    }

    // Call acc_wait_any with the array of async-arguments
    int result = acc_wait_any(NUM_TEST_CALLS, wait_arg);

    // Check if the result is -1, indicating that all async-arguments are acc_async_sync
    if (result == -1) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test NUM_TEST_CALLS times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}