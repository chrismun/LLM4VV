#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:2.7-3.3

int test1(){
    int err = 0;
    srand(SEED);

    // Attempt to set device type to none and check.
    acc_set_device_type(acc_device_none);
    if (acc_get_device_type() != acc_device_none){
        ++err;
    }

    // Try setting the device type to gpu if possible, as a more realistic test scenario than none.
    // Note: This assumes GPUs are available. If not, adjust to a device type you expect to be available such as acc_device_host.
    acc_set_device_type(acc_device_gpu);
    if (acc_get_device_type() != acc_device_gpu){
        ++err;
    }
    
    // Reset device type to default at the end for cleanliness.
    acc_set_device_type(acc_device_default);
    
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