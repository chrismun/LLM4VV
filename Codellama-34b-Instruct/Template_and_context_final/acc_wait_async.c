#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new async queue
    int async_queue = acc_async_queue_create();

    // Create a new async handle
    int async_handle = acc_async_handle_create();

    // Enqueue a wait operation on the async queue
    acc_wait_async(async_handle, async_queue);

    // Check if the wait operation has completed
    if (acc_async_handle_test(async_handle) == 0) {
        // The wait operation has completed, so we can proceed
        err = 0;
    } else {
        // The wait operation has not completed, so we need to wait
        acc_wait_async(async_handle, async_queue);
    }

    // Clean up the async queue and handle
    acc_async_queue_destroy(async_queue);
    acc_async_handle_destroy(async_handle);

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