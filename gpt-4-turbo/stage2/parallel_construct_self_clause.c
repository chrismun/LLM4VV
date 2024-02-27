#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// This function tests a basic parallel operation to simulate checking the OpenACC implementation.
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 1024;
    float a[size], b[size], c[size];

    // Initialize arrays
    for (int i = 0; i < size; ++i) {
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
        c[i] = 0.0f;
    }

    // Test OpenACC parallel construct
    #pragma acc parallel loop copyin(a[0:size],b[0:size]) copyout(c[0:size])
    for (int i = 0; i < size; ++i) {
        c[i] = a[i] + b[i];
    }

    // Verify the computation
    for (int i = 0; i < size; ++i) {
        if (abs(c[i] - (a[i] + b[i])) > 0.0001) {
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
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    if (failcode == 0) {
        printf("Test Passed: OpenACC parallel construct is working as expected.\n");
    } else {
        printf("Test Failed: Errors were detected in the OpenACC parallel construct implementation.\n");
    }

    return failcode;
}