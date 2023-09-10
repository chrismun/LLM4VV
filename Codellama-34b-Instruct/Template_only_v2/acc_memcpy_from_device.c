#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device array
    int *device_array = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the device array with random values
    for (int i = 0; i < 10; i++) {
        device_array[i] = rand();
    }

    // Create a host array
    int *host_array = (int *)malloc(sizeof(int) * 10);

    // Copy the device array to the host array using acc memcpy from device
    acc_memcpy_from_device(host_array, device_array, sizeof(int) * 10);

    // Check that the host array contains the same values as the device array
    for (int i = 0; i < 10; i++) {
        if (host_array[i] != device_array[i]) {
            err = 1;
            break;
        }
    }

    // Free the device and host arrays
    acc_free(device_array);
    free(host_array);

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