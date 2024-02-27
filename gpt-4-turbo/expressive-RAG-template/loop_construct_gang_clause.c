#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// T1: loop construct gang clause, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 128; // Assumes at least a few gangs can be utilized
    int a[size];
    int b[size];
    int expected[size];

    // Initialize data and expectations
    for(int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        expected[i] = a[i] + b[i];     
    }

    // Parallel computation using gang clause
    #pragma acc parallel loop gang
    for(int i = 0; i < size; ++i) {
        a[i] += b[i];
    }

    // Verification
    for(int i = 0; i < size; ++i) {
        if(a[i] != expected[i]) {
            err++;
            break; // Early exit on first error
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}