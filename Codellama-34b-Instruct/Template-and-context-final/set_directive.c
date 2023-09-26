#include "acc_testsuite.h"

#ifndef T1
//T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Set the default asynchronous queue to the initial value
    #pragma acc set default_async(acc_async_default)

    // Set the device number to a random value
    int device_num = rand() % 10;
    #pragma acc set device_num(device_num)

    // Set the device type to a random value
    int device_type = rand() % 2;
    #pragma acc set device_type(device_type)

    // Set the default asynchronous queue to the initial value
    #pragma acc set default_async(acc_async_default)

    // Check that the device number and device type are set correctly
    if (acc_get_device_num() != device_num || acc_get_device_type() != device_type) {
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