#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(42); // Seed for consistency in test runs.

    const int n = 100;
    int data[n];
    int tmp;

    // Initialize array with zeroes.
    for (int i = 0; i < n; ++i) {
        data[i] = 0;
    }

    // Parallel region where each thread updates data[i] with a unique value determined by private tmp.
#pragma acc parallel num_gangs(10) num_workers(10) vector_length(1) private(tmp)
    {
#pragma acc loop gang
        for (int i = 0; i < n; ++i) {
            tmp = i; // Each gang (and thus each thread) gets its own copy of tmp.
#pragma acc loop worker
            for (int j = 0; j < 1; ++j) { // This loop is trivial for this example, but it helps demonstrate the concept.
                data[i] = data[i] + tmp;
            }
        }
    }

    // Verification step.
    for (int i = 0; i < n; ++i) {
        if (data[i] != i) {
            err++;
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

    failed = test1();
    if (failed != 0) {
        failcode = failcode + 1;
        printf("Test failed with %d errors.\n", failed);
    } else {
        printf("Test passed.\n");
    }

    return failcode;
}