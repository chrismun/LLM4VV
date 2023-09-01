#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Create two arrays on the device
    int *A = (int *)acc_malloc(sizeof(int) * 10);
    int *B = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the arrays on the device
    for (int i = 0; i < 10; i++) {
        A[i] = i;
        B[i] = 0;
    }

    // Copy the contents of A to B using acc_memcpy
    acc_memcpy(B, A, sizeof(int) * 10);

    // Check that the contents of B are the same as A
    for (int i = 0; i < 10; i++) {
        if (B[i] != A[i]) {
            err = 1;
            break;
        }
    }

    // Free the arrays on the device
    acc_free(A);
    acc_free(B);

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