#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:wait clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    const int size = 1024;
    float *a = (float *)malloc(size * sizeof(float));
    float *b = (float *)malloc(size * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    int async_tag1 = 1;
    int async_tag2 = 2;

    // Copy data to device asynchronously using async_tag1
    #pragma acc enter data copyin(a[0:size]) async(async_tag1)

    // Perform computation on device asynchronously after async_tag1 has completed
    #pragma acc parallel loop copyout(b[0:size]) wait(async_tag1) async(async_tag2)
    for (int i = 0; i < size; ++i) {
        b[i] = a[i] * 2;
    }

    // Make sure the computation is completed before proceeding
    #pragma acc wait(async_tag2)

    // Verify the result
    for (int i = 0; i < size; ++i) {
        if (b[i] != a[i] * 2) {
            err += 1;
        }
    }

    // Cleanup
    #pragma acc exit data delete(a[0:size], b[0:size])

    free(a);
    free(b);

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

    if (failcode) {
        printf("FAILED: One or more tests failed.\n");
    } else {
        printf("PASSED: All tests were successful.\n");
    }

    return failcode;
}