#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the test variable
    int testVar = rand(); // Random initial value
    int originalValue = testVar; // Preserve the initial value for comparison

    // Using OpenACC serial to isolate the test feature
    #pragma acc serial firstprivate(testVar)
    {
        // This is within the serial region associated with OpenACC
        // Modify the test variable
        testVar += 5; // Increment the variable to test firstprivate

        // Note: No need to verify the value of `testVar` here as `firstprivate`
        // ensures it starts with the value `originalValue` had before entering
        // this region, the modification here won't affect `originalValue`.
    }

    // Verify that the original value outside the serial region is not changed.
    if (testVar != originalValue) {
        // If they are not equal, the firstprivate clause did not work as expected.
        err += 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    // Print test results
    if (failcode == 0) {
        printf("Test PASSED\n");
    } else {
        printf("Test FAILED\n");
    }
    return failcode;
}