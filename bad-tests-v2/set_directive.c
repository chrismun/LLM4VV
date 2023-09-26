#include "acc_testsuite.h"

#ifndef T1
//T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the default asynchronous queue to the initial value
    #pragma acc set default_async(acc_async_default)

    // Set the device number to a valid device number
    #pragma acc set device_num(1)

    // Set the device type to a valid device type
    #pragma acc set device_type(acc_device_type_gpu)

    // Check that the default asynchronous queue is set to the initial value
    if (acc_default_async_var != acc_async_default){
        err = 1;
    }

    // Check that the device number is set to the specified value
    if (acc_current_device_num_var != 1){
        err = 1;
    }

    // Check that the device type is set to the specified value
    if (acc_current_device_type_var != acc_device_type_gpu){
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