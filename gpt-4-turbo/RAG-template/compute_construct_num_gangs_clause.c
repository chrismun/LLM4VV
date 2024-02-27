#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:{compute_construct_num_gangs},V:2.7-3.3
int test1() {
    int err = 0;
    const int expected_gangs = 100; // Example number of gangs
    int actual_gangs = 0;
    srand(SEED);

    // Use OpenACC to parallelize this operation with a fixed number of gangs.
    #pragma acc parallel num_gangs(expected_gangs) copy(actual_gangs)
    {
        // Use only one thread per gang to avoid race conditions
        #pragma acc loop gang reduction(+:actual_gangs)
        for (int i = 0; i < expected_gangs; ++i) {
            actual_gangs += 1;
        }
    }

    // Verify that the expected number of gangs matches the actual execution count.
    if (actual_gangs != expected_gangs) {
        err++;
        printf("Test failed: Expected %d gangs, but got %d.\n", expected_gangs, actual_gangs);
    }
    
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