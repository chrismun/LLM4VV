#include <iostream>
#include <stdlib.h>

// Mocking this include for the sake of completeness - in a real test suite, it would provide necessary utilities.
#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct num_gangs clause, V:2.7-3.3
int test1() {
    int err = 0; // Assuming err non-zero signifies failure
    srand(SEED);

    int testData = 0;
    
    // Simulated scenario: Check if compiler ignores num_gangs in serial context.
    #pragma acc serial num_gangs(10)
    {
        testData = 1;
    }

    // Checking testData value to ensure the serial block was executed as intended despite the num_gangs clause.
    if (testData != 1) {
        err = 1; // If testData is not 1, something went wrong.
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
        failed = failed + test1(); // Aggregating results, "failed" accumulates any errors.
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0); // Bitwise operation to mark specific test fail in failcode.
    }
#endif
    return failcode;
}