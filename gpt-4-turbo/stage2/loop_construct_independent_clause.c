#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Prototyping the test function
int test_independent_loop();

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_independent_loop();
    }
    if (failed != 0) {
        failcode += 1; // Setting the first bit if there's a failure
    }

    return failcode;
}

// Function to test the independent loop clause
int test_independent_loop() {
    const int size = 1000;
    int err = 0;
    int array[size];

    // Seed for repeatability
    srand(SEED);

    // Initialize array with random values
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100; // Random number between 0-99
    }

    // Use OpenACC to double each element, assuming independent iterations
    #pragma acc parallel loop independent
    for (int i = 0; i < size; i++) {
        array[i] *= 2;
    }

    // Check to ensure that each element is indeed doubled
    for (int i = 0; i < size; i++) {
        int expected = array[i] / 2;
        if (expected != rand() % 100) {
            printf("Mismatch found at array[%d], expected %d, found %d.\n", i, expected, array[i]);
            err++;
        }
        // Reset seed to maintain synchronization
        srand(SEED);
        // Skipping ahead in the random sequence to match the initial filling of the array
        for (int skip = 0; skip <= i; ++skip) {
            rand(); 
        }
    }

    return err;
}