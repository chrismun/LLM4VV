#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new device
    acc_device_t device;
    acc_device_create(&device, acc_device_default);

    // Create a new context
    acc_context_t context;
    acc_context_create(&context, device);

    // Create a new queue
    acc_queue_t queue;
    acc_queue_create(&queue, context);

    // Attach the queue to the device
    acc_attach_queue(queue, device);

    // Detach the queue from the device
    acc_detach_queue(queue, device);

    // Destroy the queue
    acc_queue_destroy(queue);

    // Destroy the context
    acc_context_destroy(context);

    // Destroy the device
    acc_device_destroy(device);

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