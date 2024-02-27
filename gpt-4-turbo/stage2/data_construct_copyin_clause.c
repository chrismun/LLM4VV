#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Assuming definition of SEED and NUM_TEST_CALLS or setting them here for simplicity
#define SEED 12345
#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    const int SIZE = 100;
    int hostArray[SIZE];

    // Initialize the array with some values
    srand(SEED);
    for (int i = 0; i < SIZE; ++i) {
        hostArray[i] = rand() % 100; // Random values between 0 and 99
    }

    // Using the copyin clause to copy data to the device
    #pragma acc data copyin(hostArray)
    {
        // On device: Perform some operation that doesn't modify the `hostArray` to validate copyin
        #pragma acc parallel loop
        for (int i = 0; i < SIZE; ++i) {
            // Do some read-only operation, ensuring not modifying hostArray
            int temp = hostArray[i] * 2; // Dummy operation
        }
    }

    // Now verify `hostArray` remains unchanged
    srand(SEED); // Reseed to generate the same sequence of pseudo-random numbers
    for (int i = 0; i < SIZE; ++i) {
        if (hostArray[i] != (rand() % 100)) { // Compare with same initial values
            // Array was altered, which is incorrect for copyin
            err++;
            break;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }

    return failcode;
}