#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;

    // Create an array of asynchronous queues
    int async_queues[2];
    async_queues[0] = acc_async_sync;
    async_queues[1] = acc_async_sync;

    // Create a compute construct
    #pragma acc parallel num_gangs(1)
    {
        // Create a kernel that will execute asynchronously
        #pragma acc kernels async(async_queues[0])
        {
            // Do some work
            int i = 0;
            #pragma acc loop
            for (i = 0; i < 100; i++) {
                // Do some work
            }
        }

        // Create another kernel that will execute asynchronously
        #pragma acc kernels async(async_queues[1])
        {
            // Do some work
            int i = 0;
            #pragma acc loop
            for (i = 0; i < 100; i++) {
                // Do some work
            }
        }
    }

    // Wait for any of the asynchronous queues to complete
    int index = acc_wait_any(2, async_queues);

    // Check that the correct queue completed
    if (index != 0 && index != 1) {
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