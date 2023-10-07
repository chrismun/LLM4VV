#include "acc_testsuite.h"

#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;

    // create an asynchronous operation
    #pragma acc parallel async(1)
    {
        // do some work
    }

    // wait for the asynchronous operation to complete
    #pragma acc wait(1)

    // check that the asynchronous operation has completed
    if (acc_async_test(1) != 0) {
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