#include <stdio.h>
#include <stdlib.h> // For rand(), srand()
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// A simple test function to check OpenACC kernels num_workers clause
int test1() {
    int err = 0;
    srand(SEED);
    
    const int size = 1024;
    float a[size], b[size], c[size];
    float scalar = 2.0;

    // Initialize arrays with random values
    for (int i = 0; i < size; ++i) {
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
        c[i] = 0.0f;
    }

    // Use OpenACC kernels with num_workers clause
    #pragma acc kernels num_workers(4)
    for (int i = 0; i < size; ++i) {
        c[i] = a[i] + scalar * b[i];
    }

    // Verify the computation - a simple error checking
    for (int i = 0; i < size; ++i) {
        if (abs(c[i] - (a[i] + scalar * b[i])) > 1e-5) {
            err++;
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