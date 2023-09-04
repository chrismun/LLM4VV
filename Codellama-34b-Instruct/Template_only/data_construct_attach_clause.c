#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data region
    #pragma acc data
    {
        // Create a variable to store the result of the computation
        int result;

        // Attach the variable to the data region
        #pragma acc attach(result)

        // Perform a computation on the data region
        #pragma acc parallel
        {
            // Compute the result
            result = 2 * 2;
        }

        // Detach the variable from the data region
        #pragma acc detach(result)
    }

    // Check the result
    if (result != 4){
        err = 1;
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