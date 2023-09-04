#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Create a pointer to a dynamically allocated array
    int* arr = (int*)malloc(10 * sizeof(int));

    // Initialize the array with random values
    for (int i = 0; i < 10; i++) {
        arr[i] = rand();
    }

    // Create an OpenACC region with the delete clause
    #pragma acc parallel loop delete(arr)
    for (int i = 0; i < 10; i++) {
        // Do some work with the array
        arr[i] += 1;
    }

    // Check that the array has been deleted
    if (arr != NULL) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure it passes consistently
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}