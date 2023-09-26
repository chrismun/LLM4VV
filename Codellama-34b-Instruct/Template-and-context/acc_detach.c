#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Create a device array
    int *dev_data;
    acc_malloc(&dev_data, sizeof(int) * 10);

    // Copy data to device
    acc_memcpy_to_device(dev_data, data, sizeof(int) * 10);

    // Detach device memory
    acc_detach(dev_data);

    // Check if device memory is still accessible
    int *dev_data_ptr = (int *)acc_deviceptr(dev_data);
    if (dev_data_ptr == NULL) {
        // Device memory is not accessible
        err = 1;
    }

    // Free device memory
    acc_free(dev_data);

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