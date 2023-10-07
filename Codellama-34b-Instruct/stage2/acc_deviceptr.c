#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate a host array
    int *host_array = (int *)malloc(sizeof(int) * 10);

    // Initialize the host array with random values
    for (int i = 0; i < 10; i++) {
        host_array[i] = rand();
    }

    // Create a device pointer for the host array
    int *device_ptr = (int *)acc_deviceptr(host_array);

    // Check that the device pointer is not null
    if (device_ptr == NULL) {
        err = 1;
    }

    // Check that the device pointer points to the correct location in device memory
    if (device_ptr != host_array) {
        err = 1;
    }

    // Free the host array
    free(host_array);

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