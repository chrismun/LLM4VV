#include "acc_testsuite.h"

#ifndef T1
//T1:async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a parallel region with the async clause
    #pragma acc parallel async(acc_async_sync)
    {
        // Do some work in the parallel region
        #pragma acc loop
        for (int i = 0; i < 100; i++) {
            // Do some work in the loop
        }
    }

    // Check that the async clause was applied correctly
    if (acc_async_sync != acc_async_noval) {
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