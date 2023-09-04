#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set the device number to a random value
    int device_num = rand() % 10;

    // Create a new device context
    acc_device_t device = acc_get_device(device_num);

    // Set the device number for the current device
    acc_set_device_num(device, device_num);

    // Check that the device number was set correctly
    if (acc_get_device_num(device) != device_num) {
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