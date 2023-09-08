#include "acc_testsuite.h"

#ifndef T1
//T1:acc get device type,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the device type to a known value
    acc_set_device_type(ACC_DEVICE_TYPE_GPU);

    // Get the device type and check that it matches the expected value
    acc_device_t device_type = acc_get_device_type();
    if (device_type != ACC_DEVICE_TYPE_GPU) {
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