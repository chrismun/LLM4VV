#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
// T1: {loops}, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 1000;
    int *a = (int *)malloc(size * sizeof(int));
    int *results = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        a[i] = rand() / (RAND_MAX / 100);
    }

    // Assuming a device is present and can execute in parallel
#pragma acc data copy(a[0:size])
    {
#pragma acc parallel loop auto
        for (int i = 0; i < size; ++i) {
            results[i] = a[i] + 1;
        }
    }

    // Verification
    for (int i = 0; i < size; ++i) {
        if (results[i] != a[i] + 1) {
            err++;
            break;
        }
    }

    free(a);
    free(results);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    if (failcode) {
        printf("Test Failed\n");
    } else {
        printf("Test Passed\n");
    }
    return failcode;
}