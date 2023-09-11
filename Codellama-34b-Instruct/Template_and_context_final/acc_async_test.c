#include "acc_testsuite.h"

#ifndef T1
//T1:acc async test,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create an async queue
    acc_async_queue_t queue;
    acc_async_queue_create(&queue);

    // Create a device
    acc_device_t device;
    acc_device_create(&device, ACC_DEVICE_TYPE_GPU);

    // Create a kernel
    acc_kernel_t kernel;
    acc_kernel_create(&kernel, device, "my_kernel");

    // Launch the kernel asynchronously
    acc_async_launch(kernel, queue);

    // Wait for the kernel to complete
    acc_async_wait(queue);

    // Check if the kernel completed successfully
    if (acc_async_test(queue) != 0) {
        err = 1;
    }

    // Clean up
    acc_async_queue_destroy(queue);
    acc_device_destroy(device);
    acc_kernel_destroy(kernel);

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