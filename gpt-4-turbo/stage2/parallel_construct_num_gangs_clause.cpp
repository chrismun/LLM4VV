#include <iostream>
#include <stdlib.h>     // For rand(), srand()
#include <openacc.h>    // For OpenACC API

// Simple seed for reproducibility
#define SEED 42
#define NUM_TEST_CALLS 10

#ifndef T1
// T1:parallel construct num_gangs clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 1000;
    const int numGangs = 10;
    int a[size] = {0};

    // Parallel region with a specified number of gangs
    #pragma acc parallel num_gangs(numGangs) copy(a)
    {
        #pragma acc loop
        for (int i = 0; i < size; ++i) {
            a[i]++;
        }
    }

    // Check for correctness
    for (int i = 0; i < size; ++i) {
        if (a[i] != 1) {
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
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}