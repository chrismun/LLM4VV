#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new asynchronous queue
    acc_queue_t queue;
    acc_queue_create(&queue, NULL);

    // Create a new asynchronous task
    acc_task_t task;
    acc_task_create(&task, queue, NULL);

    // Wait for the task to complete
    acc_wait_async(task, NULL);

    // Check if the task completed successfully
    if (acc_task_get_status(task) != ACC_TASK_COMPLETE) {
        err = 1;
    }

    // Clean up the task and queue
    acc_task_destroy(task);
    acc_queue_destroy(queue);

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