#include "acc_testsuite.h"

#ifndef T1
//T1:acc get device num,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the device type to a valid value
    acc_device_t dev_type = acc_device_default;

    // Get the device number for the current thread
    int device_num = acc_get_device_num(dev_type);

    // Check that the device number is valid
    if (device_num < 0) {
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