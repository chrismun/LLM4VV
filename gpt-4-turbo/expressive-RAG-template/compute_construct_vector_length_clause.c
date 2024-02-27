#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// T1:compute construct vector_length clause, V:2.7-3.3
int test1() {
    int err = 0;
    const int size = 1024;
    float a[size], b[size];
    srand(SEED);

    // Initialize arrays with random values
    for (int i = 0; i < size; ++i) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = 0.0f;
    }

    // Using OpenACC parallel construct with a specified vector_length
    #pragma acc parallel loop vector_length(128)
    for (int i = 0; i < size; ++i) {
        b[i] = a[i] * 2.0f;
    }

    // Validate the results
    for (int i = 0; i < size; ++i) {
        if (b[i] != a[i] * 2.0f) {
            err++;
            break;
        }
    }
    
    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
    
    return failcode;
}