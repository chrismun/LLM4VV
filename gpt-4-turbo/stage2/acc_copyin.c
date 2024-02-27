#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test function to verify acc_copyin functionality
int test_acc_copyin() {
    int err = 0;
    const int n = 1000;
    int *hostArray = (int *)malloc(n * sizeof(int));

    // initializing array
    for (int i = 0; i < n; ++i) {
        hostArray[i] = rand() % 100; // Initialize with some random values
    }

    // Copy the array to the device and modify it on the device
    #pragma acc data copyin(hostArray[0:n])
    {
        // Modify the array on the device to see if copyin worked
        #pragma acc parallel loop
        for(int i = 0; i < n; i++) {
            hostArray[i] += 1;
        }
    }

    // Verifying if changes reflect on host side after device modification
    // Since direct checking isn't allowed, use kernel execution to validate functionality
    int valid = 1;
    for (int i = 0; i < n; ++i) {
        if (hostArray[i] % 100 == 0) { // Assuming initial value was 99 for some elements
            valid = 0;
            break;
        }
    }

    if (!valid) {
        printf("Test Failed: Changes made in the device are not reflected back to the host.\n");
        err = 1;
    } else {
        printf("Test Passed: acc_copyin works as expected.\n");
    }

    free(hostArray);
    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    srand(SEED); // Initialization, should only be called once.

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_acc_copyin();
    }

    if (failed != 0) {
        failcode += 1;
    }

    return failcode;
}