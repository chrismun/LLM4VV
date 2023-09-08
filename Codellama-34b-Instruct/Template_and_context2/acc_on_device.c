#include "acc_testsuite.h"

#ifndef T1
//T1:acc on device,V:2.7-3.3
int test1(){
    int err = 0;

    // Check if the device is a host
    if (acc_on_device(acc_device_host) == 1) {
        // If the device is a host, check if the compute region is executed on the host
        if (acc_on_device(acc_device_not_host) == 0) {
            // If the compute region is not executed on the host, return an error
            err = 1;
        }
    } else {
        // If the device is not a host, check if the compute region is executed on an accelerator
        if (acc_on_device(acc_device_not_host) == 1) {
            // If the compute region is executed on an accelerator, return an error
            err = 1;
        }
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