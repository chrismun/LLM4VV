#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    int A[10];
    int B[10];

    // Initialize arrays A and B
    for (int i = 0; i < 10; i++) {
        A[i] = i;
        B[i] = 0;
    }

    // Compute B = 2 * A using OpenACC loop with seq clause
    #pragma acc parallel loop seq
    for (int i = 0; i < 10; i++) {
        B[i] = 2 * A[i];
    }

    // Verify the result
    for (int i = 0; i < 10; i++) {
        if (B[i] != 2 * A[i]) {
            err = 1;
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
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}