#include "acc_testsuite.h"

#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the default asynchronous activity queue to a specific queue
    acc_set_default_async(1);

    // Create a compute construct with an async clause that does not specify a queue
    #pragma acc parallel async
    {
        // Do some work
    }

    // Check that the work was executed asynchronously in the default queue
    if (acc_get_async_queue() != 1) {
        err = 1;
    }

    // Reset the default asynchronous activity queue to the initial value
    acc_set_default_async(acc_async_default);

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