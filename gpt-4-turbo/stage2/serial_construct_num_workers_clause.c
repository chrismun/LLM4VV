#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:serial construct, num_workers clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int testValue = 0;
    int hostValue = 0;

#pragma acc serial num_workers(4) copy(testValue)
    {
        testValue += 1;
    }

    hostValue += 1;

    // Compare the results
    if (testValue != hostValue) {
        err = 1; // If there's any discrepancy, it indicates an error.
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