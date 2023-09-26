#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device array
    int *dev_array = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the device array with random values
    for (int i = 0; i < 10; i++) {
        dev_array[i] = rand();
    }

    // Update the device array with new values
    for (int i = 0; i < 10; i++) {
        dev_array[i] = rand();
    }

    // Check that the device array has been updated correctly
    for (int i = 0; i < 10; i++) {
        if (dev_array[i] != rand()) {
            err = 1;
            break;
        }
    }

    // Free the device array
    acc_free(dev_array);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}