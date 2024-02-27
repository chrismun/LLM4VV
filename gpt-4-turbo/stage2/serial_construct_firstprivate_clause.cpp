// Include necessary header files
#include <iostream>
#include <stdlib.h>

// Assuming acc_testsuite.h sets up necessary testing environment
// Dummy file for the sake of this example.
#include "acc_testsuite.h"

#ifndef T1
// T1:serial construct firstprivate clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int initialValue = rand();
    int testValue = -1;  // Initialize with a value that will be replaced.

    // The OpenACC block where we test the firstprivate clause.
    #pragma acc serial firstprivate(initialValue) copyout(testValue)
    {
        testValue = initialValue; // The initialValue should be preserved here.
    }

    // Check if testValue equals initialValue.
    if (testValue != initialValue) {
        err++;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}