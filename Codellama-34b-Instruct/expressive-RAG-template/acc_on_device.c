#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device and a queue
    acc_device_t device = acc_get_device(acc_device_default);
    acc_queue_t queue = acc_get_queue(device);

    // Allocate memory on the device
    size_t size = 1024;
    void* device_ptr = acc_malloc(size);

    // Initialize the memory on the device
    acc_memset(device_ptr, 0, size);

    // Create a kernel that writes to the device memory
    acc_kernel_t kernel = acc_create_kernel(device, "my_kernel", 1, 1);
    acc_set_kernel_arg(kernel, 0, device_ptr);

    // Launch the kernel on the device
    acc_launch_kernel(kernel, 1, 1, 1);

    // Synchronize the device
    acc_synchronize_device(device);

    // Check the result
    if (acc_get_device_memory(device_ptr) != 0) {
        err = 1;
    }

    // Free the device memory
    acc_free(device_ptr);

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