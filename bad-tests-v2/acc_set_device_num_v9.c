#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set the device number to a random value
    int device_num = rand() % 10;

    // Create an OpenACC device object
    acc_device_t device;
    acc_device_create(&device, device_num);

    // Set the device number on the device object
    acc_set_device_num(device, device_num);

    // Verify that the device number was set correctly
    if (acc_get_device_num(device) != device_num) {
        err = 1;
    }

    // Clean up the device object
    acc_device_destroy(device);

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