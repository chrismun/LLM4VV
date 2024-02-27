#include <cstdlib>
#include <iostream>

// Assuming this is provided based on the template request; implement if absent.
// These would typical include definitions for SEED and NUM_TEST_CALLS at least.
#include "acc_testsuite.h"

#ifndef T1
// T1:routine directive,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Target function for device, not expected to be callable on host due to nohost
    #pragma acc routine seq nohost
    auto deviceFunction = []() -> int {
        return 42; // Arbitrary computation
    };

    int result = 0;

    // Attempt to execute on device, value should be set if execution is successful
    #pragma acc parallel copy(result)
    {
        result = deviceFunction();
    }

    // Verifying if the execution happened correctly
    if (result != 42) {
        // The expected value was not returned; this signifies an error in executing or retrieving from the device
        err = 1;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}