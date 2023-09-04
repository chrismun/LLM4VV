#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new OpenACC context
    acc_context_t context = acc_create_context();

    // Create a new OpenACC queue
    acc_queue_t queue = acc_create_queue(context);

    // Create a new OpenACC device
    acc_device_t device = acc_create_device(context, 0);

    // Create a new OpenACC kernel
    acc_kernel_t kernel = acc_create_kernel(context, "my_kernel");

    // Set the kernel to run asynchronously
    acc_set_kernel_async(kernel, 1);

    // Launch the kernel
    acc_launch_kernel(kernel, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    // Wait for the kernel to complete
    acc_wait_async(queue, kernel);

    // Check if the kernel completed successfully
    if (acc_get_kernel_status(kernel) != ACC_KERNEL_COMPLETED) {
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