#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T2
// T2:routine, V:1.0-2.7

// Define a simple function to be marked as a routine
#pragma acc routine seq
int add(int a, int b) {
    return a + b;
}

int test_routine_directive() {
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *result = (int *)malloc(n * sizeof(int));
    int *expected = (int *)malloc(n * sizeof(int));

    // Initialize arrays with random integers and compute expected results
    for (int x = 0; x < n; ++x) {
        a[x] = rand() % 100;
        b[x] = rand() % 100;
        expected[x] = add(a[x], b[x]);  // Compute expected result using CPU
    }

    // Compute results on the accelerator
    #pragma acc parallel copyin(a[0:n], b[0:n]) copyout(result[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x) {
            result[x] = add(a[x], b[x]);  // Use the routine on the accelerator
        }
    }

    // Check results against expectations
    for (int x = 0; x < n; ++x) {
        if (result[x] != expected[x]) {
            err++;
        }
    }

    free(a);
    free(b);
    free(result);
    free(expected);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_routine_directive();
    }

    if (failed != 0) {
        failcode += (1 << 1);
    }

    return failcode;
}