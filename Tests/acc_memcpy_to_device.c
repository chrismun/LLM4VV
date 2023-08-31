#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <accelerator.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Create a host array and fill it with random data
    int *host_array = (int *)malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        host_array[i] = rand();
    }

    // Create a device array and copy the host array to it
    int *device_array = (int *)malloc(sizeof(int) * 100);
    acc_memcpy(device_array, host_array, sizeof(int) * 100);

    // Check that the device array contains the same data as the host array
    for (int i = 0; i < 100; i++) {
        if (device_array[i] != host_array[i]) {
            err = 1;
            break;
        }
    }

    // Free the host and device arrays
    free(host_array);
    free(device_array);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}