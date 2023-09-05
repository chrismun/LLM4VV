#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an async queue
    acc_async_queue_t queue;
    acc_async_queue_create(&queue);

    // Create an async operation
    acc_async_operation_t operation;
    acc_async_operation_create(&operation, queue);

    // Wait for the async operation to complete
    acc_wait(operation);

    // Check if the async operation completed successfully
    if (acc_async_operation_status(operation) != ACC_ASYNC_OPERATION_COMPLETE) {
        err = 1;
    }

    // Clean up the async queue and operation
    acc_async_queue_destroy(queue);
    acc_async_operation_destroy(operation);

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