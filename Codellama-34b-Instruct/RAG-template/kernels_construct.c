#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct,V:2.7-3.3
int test1(){
    int err = 0;

    // Define a kernel function
    void kernel_function(int* data) {
        // Do some computation on the data
        for (int i = 0; i < 100; i++) {
            data[i] = data[i] + 1;
        }
    }

    // Create a device array
    int* device_data = (int*)acc_malloc(100 * sizeof(int));

    // Initialize the device array
    for (int i = 0; i < 100; i++) {
        device_data[i] = i;
    }

    // Launch the kernel
    acc_kernels(kernel_function, device_data);

    // Synchronize the device
    acc_sync(device_data);

    // Check the result
    for (int i = 0; i < 100; i++) {
        if (device_data[i] != i + 1) {
            err++;
        }
    }

    // Free the device array
    acc_free(device_data);

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