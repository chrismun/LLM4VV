#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Defining constants for the test
#define ARRAY_SIZE 100
#define SEED 12345
#define NUM_TEST_CALLS 10

// Function to test the copyout clause
int test_copyout() {
    int err = 0;
    int *a_host, *a_device;

    // Allocate memory on the host
    a_host = (int*)malloc(ARRAY_SIZE * sizeof(int));

    // Initialize array elements to 0 on host
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a_host[i] = 0;
    }

    // Allocate memory on the device and use copyout to reflect changes on a_host
#pragma acc data create(a_device[0:ARRAY_SIZE]) copyout(a_host[0:ARRAY_SIZE])
    {
#pragma acc parallel loop
        for (int i = 0; i < ARRAY_SIZE; i++) {
            a_device[i] = i;
        }
    }

    // Verify if changes made in parallel region are reflected on the host
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (a_host[i] != i) {
            err++;
        }
    }

    // Clean up
    free(a_host);

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_copyout();
    }

    if (failed != 0) {
        failcode = 1; // Indicate failure
        printf("Test FAILED with %d errors.\n", failed);
    } else {
        printf("Test PASSED.\n");
    }

    return failcode;
}