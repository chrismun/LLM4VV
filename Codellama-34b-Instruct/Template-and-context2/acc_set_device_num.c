#include "acc_testsuite.h"

#ifndef T1
//T1:acc set device num,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_TYPE_CPU);

    // Set the device number to 0
    acc_set_device_num(0, ACC_DEVICE_TYPE_CPU);

    // Check that the device number is set correctly
    if (acc_get_device_num() != 0) {
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