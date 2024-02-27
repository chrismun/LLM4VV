#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Assuming definitions for SEED and NUM_TEST_CALLS
#define SEED 12345
#define NUM_TEST_CALLS 10

// Test for OpenACC compute construct with the default(none) clause
int test_compute_construct_default_none() {
    const int size = 1024;
    int a[size];
    int err = 0;

    // Initializing data
    for (int i = 0; i < size; i++) {
        a[i] = -1;
    }

    // OpenACC parallel region with default(none) requiring explicit data clause
    #pragma acc parallel loop default(none) copyout(a[0:size])
    for (int i = 0; i < size; i++) {
        a[i] = i;
    }

    // Verify the computation
    for (int i = 0; i < size; i++) {
        if (a[i] != i) {
            err++;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_compute_construct_default_none();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}