#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Create an array of size 100
    int arr[100];

    // Initialize the array with random values
    for (int i = 0; i < 100; i++) {
        arr[i] = rand();
    }

    // Create a new array with the same size and type as the original array
    int new_arr[100];

    // Copy the values from the original array to the new array using the create clause
    #pragma acc parallel loop copy(arr[0:100]) create(new_arr[0:100])
    for (int i = 0; i < 100; i++) {
        new_arr[i] = arr[i];
    }

    // Check if the values in the new array are the same as the original array
    for (int i = 0; i < 100; i++) {
        if (new_arr[i] != arr[i]) {
            err = 1;
            break;
        }
    }

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