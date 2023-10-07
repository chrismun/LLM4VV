#include "acc_testsuite.h"
#ifndef T1
//T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;
    int device_type = 1; // Assuming device type 1 is available
    int device_num = 0; // Using default device
    int async_val = acc_async_sync; // Setting async operations to synchronous

    #pragma acc set device_type(device_type) device_num(device_num) default_async(async_val)

    // Check if the set directive was successful by verifying the values of the control variables
    if (acc_get_device_type() != device_type || acc_get_device_num() != device_num || acc_get_default_async() != async_val){
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