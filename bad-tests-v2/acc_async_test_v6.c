#include "acc_testsuite.h"

#ifndef T1
//T1:acc async test,V:2.7-3.3
int test1(){
    int err = 0;

    // complete the test here
    int wait_arg = 0;
    int dev_num = 0;
    int async_queue = 0;

    // create an async queue
    async_queue = acc_async_queue_create(dev_num);

    // create an async operation
    acc_async_operation_create(async_queue, wait_arg);

    // test for completion of the async operation
    if (acc_async_test(wait_arg) == 0) {
        // async operation has not completed
        err = 1;
    }

    // clean up
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