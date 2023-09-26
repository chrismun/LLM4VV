#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new OpenACC context
    acc_context_t context = acc_create_context(ACC_DEVICE_HOST, ACC_CONTEXT_DEFAULT);

    // Create a new OpenACC queue
    acc_queue_t queue = acc_create_queue(context, ACC_QUEUE_DEFAULT);

    // Create a new OpenACC event
    acc_event_t event = acc_create_event(context, ACC_EVENT_DEFAULT);

    // Set the event to be triggered when the queue is empty
    acc_set_event(queue, event, ACC_EVENT_QUEUE_EMPTY);

    // Wait for the event to be triggered
    acc_wait_async(queue, event);

    // Check if the event was triggered
    if (acc_get_event_status(event) == ACC_EVENT_STATUS_TRIGGERED) {
        // The event was triggered, so the queue is empty
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