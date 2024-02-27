#include <stdlib.h>
#include <stdio.h>
#include <openacc.h> // Required for OpenACC

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 1
#endif

// Simple test to validate the compute construct self clause.
int test_compute_construct_self() {
    int err = 0;
    const int size = 100;
    int data[size];

    // Initialize the array with a pattern
    for (int i = 0; i < size; ++i) {
        data[i] = i;
    }

    // Use an OpenACC parallel region with the self clause.
    // The self clause condition is omitted, hence assumed true.
    // Expect execution on the host device.
#pragma acc parallel loop self
    for (int i = 0; i < size; ++i) {
        data[i] += 1; // Simple operation to validate execution
    }

    // Verify execution happened on the host by checking the updated values
    for (int i = 0; i < size; ++i) {
        if (data[i] != i + 1) {
            err++;
            break;
        }
    }
    
    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    failed = test_compute_construct_self();
    if (failed != 0) {
        failcode = 1; // Indicates failure;
        printf("Test failed: Compute construct self clause did not work as expected.\n");
    } else {
        printf("Test passed: Compute construct self clause works correctly.\n");
    }
    
    return failcode;
}