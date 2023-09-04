#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new OpenACC device
    acc_device_t device;
    acc_device_create(&device, acc_device_default);

    // Create a new OpenACC context
    acc_context_t context;
    acc_context_create(&context, device);

    // Create a new OpenACC queue
    acc_queue_t queue;
    acc_queue_create(&queue, context);

    // Create a new OpenACC event
    acc_event_t event;
    acc_event_create(&event, queue);

    // Wait for any event to complete
    acc_wait_any(event);

    // Check if the event has completed
    if (acc_event_test(event) == 0) {
        // The event has completed, so we can proceed with the next step
        err = 1;
    }

    // Clean up the OpenACC resources
    acc_event_destroy(event);
    acc_queue_destroy(queue);
    acc_context_destroy(context);
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