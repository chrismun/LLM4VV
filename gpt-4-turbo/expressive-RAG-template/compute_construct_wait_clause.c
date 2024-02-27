#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef T1
// T1: compute construct wait clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(42); // SEED for reproducibility

    const int size = 10000;
    float *data = (float*)malloc(size * sizeof(float));

    // Initialize data array on the host
    for (int i = 0; i < size; ++i) {
        data[i] = (float)i;
    }

    // First asynchronous compute operation
    #pragma acc parallel loop copy(data[0:size]) async(1)
    for (int i = 0; i < size; ++i) {
        data[i] = data[i] + 1.0f;
    }

    // Second asynchronous compute operation
    // This operation must wait for the first to complete due to the wait clause
    #pragma acc parallel loop copy(data[0:size]) async(2) wait(1)
    for (int i = 0; i < size; ++i) {
        data[i] = data[i] * 2.0f;
    }

    // Wait for the second operation to complete before verifying results
    #pragma acc wait(2)

    // Verify results
    for (int i = 0; i < size; ++i) {
        if (data[i] != (i + 1.0f) * 2.0f) {
            err++;
        }
    }

    free(data);
    return err;
}
#endif

int main() {
    const int NUM_TEST_CALLS = 10; // Number of times the test is executed
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        if (test1() != 0) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    if (failcode == 0) {
        printf("PASS: Compute construct wait clause works as expected.\n");
    } else {
        printf("FAIL: Errors detected in compute construct wait clause.\n");
    }

    return failcode;
}