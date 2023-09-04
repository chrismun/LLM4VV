#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new OpenACC context
    acc_context_t context = acc_create_context(ACC_DEVICE_TYPE_GPU, ACC_DEVICE_TYPE_CPU);

    // Create a new OpenACC queue
    acc_queue_t queue = acc_create_queue(context, ACC_QUEUE_TYPE_DEFAULT);

    // Create a new OpenACC event
    acc_event_t event = acc_create_event(queue, ACC_EVENT_TYPE_DEFAULT);

    // Wait for the event to complete
    acc_wait(event);

    // Check if the event has completed
    if (acc_event_is_complete(event)) {
        // The event has completed, so we can proceed with the next step
        err = 0;
    } else {
        // The event has not completed, so we need to wait for it to complete
        err = 1;
    }

    // Clean up the OpenACC context and queue
    acc_destroy_context(context);
    acc_destroy_queue(queue);

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