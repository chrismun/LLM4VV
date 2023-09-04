#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize a device of type GPU
    acc_init_device(ACC_DEVICE_GPU);

    // Verify that the device is initialized
    if (acc_get_device_type() != ACC_DEVICE_GPU) {
        err = 1;
    }

    // Initialize a device of type CPU
    acc_init_device(ACC_DEVICE_CPU);

    // Verify that the device is initialized
    if (acc_get_device_type() != ACC_DEVICE_CPU) {
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