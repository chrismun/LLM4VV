#include "acc_testsuite.h"

#ifndef T1
/*T1:acc get num devices,V:2.0-2.7*/
int test1(){
    int err = 0;

    // Get the number of devices of a specific type
    acc_device_t dev_type = acc_device_nvidia; // Change this to the type you want to test
    int deviceCount = acc_get_num_devices(dev_type);

    // Check if device count is less than 0, which implies error
    if(deviceCount < 0){
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