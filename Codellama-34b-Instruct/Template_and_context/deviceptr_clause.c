#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Initialize a device pointer
    int *device_ptr = (int *)acc_malloc(sizeof(int));
    if (device_ptr == NULL) {
        err = 1;
    }

    // Set the device pointer to a random value
    *device_ptr = rand();

    // Verify that the device pointer is not NULL
    if (device_ptr == NULL) {
        err = 1;
    }

    // Verify that the device pointer is not the same as the host pointer
    if (device_ptr == &err) {
        err = 1;
    }

    // Free the device pointer
    acc_free(device_ptr);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}