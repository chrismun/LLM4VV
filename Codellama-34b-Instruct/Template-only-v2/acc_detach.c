#include "acc_testsuite.h"
#ifndef T1
//T1:acc detach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device and attach it to the current host thread
    acc_device_t device = acc_get_device(acc_device_default);
    acc_attach(device);

    // Detach the device from the current host thread
    acc_detach(device);

    // Check that the device is no longer attached to the current host thread
    if (acc_get_device(acc_device_default) != device) {
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