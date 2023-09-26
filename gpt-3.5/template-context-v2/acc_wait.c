#include "acc_testsuite.h"

#ifndef T1
// T1: acc wait, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc parallel
    {
        #pragma acc loop
        for (int i = 0; i < SIZE; ++i) {
          a[i] = 0;
        }
    }

    // Perform work on the CPU
    for (int i = 0; i < SIZE; ++i) {
        a[i] += b[i];
        b[i] = a[i] - b[i];
        a[i] -= b[i];
    }

    // Explicitly wait for all pending data transfers
    #pragma acc wait

    // Verify the correctness of the results
    for (int i = 0; i < SIZE; ++i) {
        if (a[i] != i) {
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
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}