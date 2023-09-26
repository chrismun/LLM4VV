#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the runtime for the specified device type and device number
    acc_init(ACC_DEVICE_TYPE_GPU);
    acc_init_device(0, ACC_DEVICE_TYPE_GPU);

    // Check if the device is initialized correctly
    if (acc_get_device_type() != ACC_DEVICE_TYPE_GPU || acc_get_device_num() != 0) {
        err = 1;
    }

    // Shut down the device
    acc_shutdown();

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