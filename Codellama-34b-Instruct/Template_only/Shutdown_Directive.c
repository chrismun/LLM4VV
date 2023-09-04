#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new OpenACC context
    acc_context_t context = acc_create_context(NULL, NULL);

    // Set the shutdown directive for the context
    acc_set_shutdown_directive(context, ACC_SHUTDOWN_DIRECTIVE_EXIT);

    // Create a new OpenACC device
    acc_device_t device = acc_create_device(context, ACC_DEVICE_TYPE_GPU);

    // Set the device as the current device for the context
    acc_set_device(context, device);

    // Create a new OpenACC queue
    acc_queue_t queue = acc_create_queue(context, device);

    // Set the queue as the current queue for the context
    acc_set_queue(context, queue);

    // Create a new OpenACC kernel
    acc_kernel_t kernel = acc_create_kernel(context, "my_kernel", NULL);

    // Set the kernel as the current kernel for the context
    acc_set_kernel(context, kernel);

    // Launch the kernel
    acc_launch_kernel(context, kernel, 0, NULL, NULL);

    // Wait for the kernel to complete
    acc_wait_kernel(context, kernel);

    // Shut down the OpenACC context
    acc_shutdown_context(context);

    // Check if the context was shut down correctly
    if (acc_get_context_status(context) != ACC_CONTEXT_STATUS_SHUTDOWN){
        err = 1;
    }

    // Clean up the OpenACC context
    acc_destroy_context(context);

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