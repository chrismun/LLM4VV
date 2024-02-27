#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Defining constants for easy modification and understanding
#define SEED 1234
#define NUM_ELEMENTS 100
#define NUM_TEST_CALLS 10

// A function to test the OpenACC serial construct reduction clause
int test_serial_reduction() {
    int err = 0;
    srand(SEED);
    int a[NUM_ELEMENTS];
    int serial_sum = 0;
    int expected_sum = 0;

    // Initialize array with random values and calculate the expected sum
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        a[i] = rand() % 100;  // Random integers between 0 and 99
        expected_sum += a[i];
    }

    // Performing the reduction in a serial construct
    #pragma acc serial reduction(+:serial_sum)
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        serial_sum += a[i];
    }

    // Check if the result of the serial reduction matches the expected sum
    if (serial_sum != expected_sum) {
        err = 1;  // Error if the sums don't match
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_serial_reduction();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    return failcode;
}