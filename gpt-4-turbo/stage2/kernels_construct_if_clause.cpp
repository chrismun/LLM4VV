// Including necessary headers
#include <iostream>
#include <stdlib.h>
#include "acc_testsuite.h"

// Test 1: Verify kernels construct if clause.
#ifndef T1
// T1: kernels construct if clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    const int size = 100;
    int *a = new int[size];

    // Initialize array to zeros
    for (int i = 0; i < size; ++i) {
        a[i] = 0;
    }

    // Randomly decide whether to execute on accelerator or not
    bool useAccelerator = rand() % 2;

    // Apply the kernels construct with an if clause
#pragma acc kernels if(useAccelerator)
    for (int i = 0; i < size; ++i) {
        a[i] = 1;
    }

    // Validate results
    for (int i = 0; i < size; ++i) {
        if (useAccelerator && a[i] != 1) {
            err++;
            break;
        }
        if (!useAccelerator && a[i] != 0) {
            err++;
            break;
        }
    }

    delete[] a;
    return err;
}
#endif

int main() {
    int failcode = 0;
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}