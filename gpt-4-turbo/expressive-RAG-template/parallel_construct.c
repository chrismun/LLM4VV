#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// A basic test suite setup, assuming these definitions are provided externally or can be adjusted as needed.
#define SEED 12345
#define NUM_TEST_CALLS 10

// Test function prototype
int test_parallel_construct();

// Main test: parallel construct
int test_parallel_construct() {
    int err = 0;
    const int size = 100;
    int original_array[size];
    int computed_array[size];
    
    // Initialize the original array with random data
    srand(SEED);
    for (int i = 0; i < size; i++) {
        original_array[i] = rand() % 100; // Random numbers between 0-99
    }
    
    // Parallel region to compute the square of each element
#pragma acc parallel num_gangs(1) copyin(original_array) copy(computed_array)
    {
        for (int i = 0; i < size; i++) {
#pragma acc loop vector
            computed_array[i] = original_array[i] * original_array[i];
        }
    }

    // Check the computed results
    for (int i = 0; i < size; i++) {
        if (computed_array[i] != original_array[i] * original_array[i]) {
            err = 1; // Incorrect computation detected
            break;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_parallel_construct();
    }
    if (failed != 0) {
        failcode = 1;
        printf("Parallel construct test FAILED.\n");
    } else {
        printf("Parallel construct test PASSED.\n");
    }
    return failcode;
}