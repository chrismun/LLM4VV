#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Assuming acc_testsuite.h defines some constants and utilities, like SEED for srand and a macro or function for NUM_TEST_CALLS
#include "acc_testsuite.h"

#ifndef T1
// T1: kernels construct, firstprivate clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    int initData = 42; // Initial data to be used with firstprivate
    const int num_elements = 1000;
    int data[num_elements];

    // Initialize array with zeros
    for (int i = 0; i < num_elements; ++i) {
        data[i] = 0;
    }

    // The kernels construct with firstprivate clause
    #pragma acc kernels firstprivate(initData) copy(data[0:num_elements])
    for (int i = 0; i < num_elements; ++i) {
        data[i] = initData; // Each thread sets its element to the initial value of initData
        initData = i; // Modify initData to check if it's indeed private and initialization is done per kernel
    }

    // Verification
    for (int i = 0; i < num_elements; ++i) {
        if (data[i] != 42) { // If firstprivate worked, all elements should be 42
            err++;
            break;
        }
    }
    return err;
}
#endif

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