#include "acc_testsuite.h"
#ifndef T1
//T1:acc get device type,V:2.7-3.3
int test1(){
    int err = 0;

    // Verification that device is default not_set
    if(acc_get_device_type() != acc_device_notset){
        err = 1;
    }

    // Setting device type to acc_device_gpu and verify if it's set
    acc_set_device_type(acc_device_gpu);
    if(acc_get_device_type() != acc_device_gpu){
        err = 1;
    }

    // Reset device type and ensure it's back to acc_device_notset
    acc_set_device_type(acc_device_notset);
    if(acc_get_device_type() != acc_device_notset){
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