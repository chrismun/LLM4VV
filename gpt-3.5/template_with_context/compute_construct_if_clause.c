#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    int condition = rand() % 2;  // Randomly set the condition to true or false

    #pragma acc compute if(condition)     // Use the if clause for the compute construct
    {
        // Code block to be executed on the current device (if condition is true)
        // This block can have any OpenACC parallel or data constructs
        // ...

        if (condition) {   // This is not required, just for validation
            // Region executed on the current device
        } else {
            // Region executed on the local thread
            err = 1;    // Mark the test as failed if condition is false
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