#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device and a kernel
    acc_device_t device;
    acc_kernel_t kernel;

    // Initialize the device and kernel
    acc_init(device);
    acc_create_kernel(kernel, "my_kernel", 1, 1);

    // Shutdown the device and kernel
    acc_shutdown(device);
    acc_destroy_kernel(kernel);

    // Check if the device and kernel are properly shutdown
    if (device.status != ACC_DEVICE_SHUTDOWN || kernel.status != ACC_KERNEL_SHUTDOWN){
        err = 1;
    }

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