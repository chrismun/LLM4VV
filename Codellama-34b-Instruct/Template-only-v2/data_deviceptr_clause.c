#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device pointer
    int *device_ptr = (int *)acc_malloc(sizeof(int));

    // Set the device pointer to a random value
    *device_ptr = rand();

    // Create a host pointer
    int *host_ptr = (int *)malloc(sizeof(int));

    // Set the host pointer to a random value
    *host_ptr = rand();

    // Copy the device pointer to the host pointer
    acc_memcpy(host_ptr, device_ptr, sizeof(int));

    // Check that the host pointer has the same value as the device pointer
    if (*host_ptr != *device_ptr) {
        err = 1;
    }

    // Free the device pointer
    acc_free(device_ptr);

    // Free the host pointer
    free(host_ptr);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}