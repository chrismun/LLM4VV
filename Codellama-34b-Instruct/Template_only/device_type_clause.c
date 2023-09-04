#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device type variable
    int device_type = acc_get_device_type();

    // Check if the device type is supported
    if (device_type == ACC_DEVICE_TYPE_GPU) {
        // If the device type is GPU, use the GPU device
        acc_set_device_type(ACC_DEVICE_TYPE_GPU);
    } else if (device_type == ACC_DEVICE_TYPE_CPU) {
        // If the device type is CPU, use the CPU device
        acc_set_device_type(ACC_DEVICE_TYPE_CPU);
    } else {
        // If the device type is not supported, return an error
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