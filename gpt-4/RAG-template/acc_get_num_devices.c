#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:acc get num devices,V:2.7-3.3
int test1(){
    int err = 0;

    // OpenACC device type.
    acc_device_t deviceType = acc_device_nvidia;

    // Get the number of available OpenACC devices.
    int numDevices = acc_get_num_devices(deviceType);

    if(numDevices <= 0){
        // If there are no OpenACC devices available, it means there's an error or the device is not supported.
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