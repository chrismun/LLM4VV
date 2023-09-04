#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device pointer
    int *device_ptr = (int *)acc_malloc(sizeof(int));

    // Initialize the device pointer with a random value
    *device_ptr = rand();

    // Create a host pointer
    int *host_ptr = (int *)malloc(sizeof(int));

    // Copy the device pointer to the host pointer
    acc_memcpy(host_ptr, device_ptr, sizeof(int));

    // Check if the host pointer has the same value as the device pointer
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

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}