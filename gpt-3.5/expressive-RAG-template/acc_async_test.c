#include "acc_testsuite.h"
#ifndef T1
// T1: acc async test, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Test acc_async_test
    int x = 1;
    int y = 2;

    // Parallel region
    #pragma acc parallel async(x)
    {
        // Some computation
        for (int i = 0; i < 1000000; i++) {
            x++;
        }

        // The result of y won't be made available before the completion of x
        // acc async test should return false in that case
        // (i.e., y's value shouldn't be updated in the async clause.
        y = x;
        //#pragma acc async(x)   We can also specify async clause directly after y = x.
    }

    // Checking the correctness of acc_async_test
    if (y != 2) {
        err = 1;
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