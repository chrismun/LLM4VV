#include "acc_testsuite.h"
#ifndef T1

int test1(){
    int err = 0;

    // Check the device type
    acc_device_t device_type = acc_get_device_type();
    if (device_type != acc_device_none && device_type != acc_device_host && device_type != acc_device_not_host){
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