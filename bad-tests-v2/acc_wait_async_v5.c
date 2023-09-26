#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait async,V:2.7-3.3
int test1(){
    int err = 0;

    // create an async queue
    int async_queue = acc_async_queue_create();

    // create a wait argument
    int wait_arg = acc_async_queue_create();

    // enqueue a wait operation on the async queue
    acc_wait_async(wait_arg, async_queue);

    // check that the wait operation has been enqueued
    if (acc_async_queue_empty(async_queue)) {
        err = 1;
    }

    // destroy the async queue
    acc_async_queue_destroy(async_queue);

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