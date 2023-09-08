#include "acc_testsuite.h"

#ifndef T1
// T1: compute construct default clause, V: 2.7-3.3
int test1() {
    int err = 0;

    // Set up data for the test
    int data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }

    // Create a compute construct with the default clause
    #pragma acc parallel default(present)
    {
        // Use the data in the compute construct
        int sum = 0;
        for (int i = 0; i < 100; i++) {
            sum += data[i];
        }

        // Check that the data is present in the compute construct
        if (sum != 4950) {
            err = 1;
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