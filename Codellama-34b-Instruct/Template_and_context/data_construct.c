#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new device memory space
    int *dev_ptr = (int *)acc_malloc(sizeof(int));

    // Copy data from local memory to device memory
    acc_memcpy_to_device(dev_ptr, &x, sizeof(int));

    // Execute a kernel on the device
    acc_kernel_launch(dev_ptr, sizeof(int));

    // Copy data from device memory to local memory
    acc_memcpy_from_device(dev_ptr, &x, sizeof(int));

    // Free device memory
    acc_free(dev_ptr);

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