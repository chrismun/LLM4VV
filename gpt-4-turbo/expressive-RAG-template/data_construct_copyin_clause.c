#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Define a small utility for seed to ensure repeatability
#define SEED 42
// Specifying a relatively small number of tests
#define NUM_TEST_CALLS 10

// Test function for the copyin clause
int test1() {
    int err = 0; // Error tracker
    srand(SEED);

    int hostArray[100];
    // Initialize array with random data
    for (int i = 0; i < 100; ++i) {
        hostArray[i] = rand() % 100;
    }

    // Expected sum of the array elements
    int expectedSum = 0;
    for (int i = 0; i < 100; ++i) {
        expectedSum += hostArray[i];
    }

    int sum = 0;
    // Using copyin clause to copy hostArray into the device
    #pragma acc parallel copyin(hostArray) reduction(+:sum)
    for (int i = 0; i < 100; ++i) {
        sum += hostArray[i];
    }

    // Verify the computation on the device matches the expected result
    if (sum != expectedSum) {
        printf("Test Failed. Expected sum: %d, Found: %d\n", expectedSum, sum);
        err = 1;
    } else {
        printf("Test Passed.\n");
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
        failcode = failcode + (1 << 0);
    }

    if (failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }

    return failcode;
}