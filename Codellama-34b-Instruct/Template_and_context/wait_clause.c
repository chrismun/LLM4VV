#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device and activity queues
    acc_device_t device = acc_get_device(acc_device_default);
    acc_async_t async = acc_async_create(device, acc_async_default);

    // Enqueue a kernel on the device
    acc_kernel_t kernel = acc_kernel_create(device, acc_kernel_default);
    acc_kernel_set_arg(kernel, 0, sizeof(int), &err);
    acc_kernel_set_arg(kernel, 1, sizeof(int), &async);
    acc_kernel_launch(kernel, 1, 1, 1);

    // Wait for the kernel to complete
    acc_wait(async);

    // Check the result
    if (err != 0) {
        return 1;
    }

    return 0;
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