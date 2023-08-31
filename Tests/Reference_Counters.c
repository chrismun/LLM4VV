#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Create an array of 100 integers
    int arr[100];
    for (int i = 0; i < 100; i++) {
        arr[i] = rand() % 100;
    }

    // Create a reference counter for the array
    int *ref_count = (int *)malloc(sizeof(int));
    *ref_count = 0;

    // Create a copy of the array
    int *copy = (int *)malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        copy[i] = arr[i];
    }

    // Increment the reference counter
    *ref_count = *ref_count + 1;

    // Check if the reference counter is correct
    if (*ref_count != 1) {
        err = 1;
    }

    // Decrement the reference counter
    *ref_count = *ref_count - 1;

    // Check if the reference counter is correct
    if (*ref_count != 0) {
        err = 1;
    }

    // Free the memory
    free(ref_count);
    free(copy);

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