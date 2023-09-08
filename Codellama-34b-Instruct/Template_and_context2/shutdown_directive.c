#include "acc_testsuite.h"

#ifndef T1
//T1:shutdown directive,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up a device
    int device_type = 1; // GPU
    int device_num = 0;
    int device_id = acc_get_device_id(device_type, device_num);

    // Shut down the device
    #pragma acc shutdown device_type(device_type) device_num(device_num)

    // Check that the device is no longer available
    if (acc_is_device_available(device_id)) {
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