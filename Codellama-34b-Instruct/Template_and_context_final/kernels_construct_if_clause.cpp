#include "acc_testsuite.h"

// T1: kernels construct if clause, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // The if clause is optional, so we can omit it if we want
    if (rand() % 2 == 0) {
        // Execute the region on the current device
        #pragma acc kernels if (rand() % 2 == 0)
        {
            // Do some work here
        }
    } else {
        // Execute the region on the local thread
        #pragma acc kernels
        {
            // Do some work here
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Test the kernels construct if clause
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}