#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:init,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Attempt to initialize the OpenACC runtime for the default device
    acc_init(acc_device_default);

    // Check if the initialization was successful by querying for the number of devices
    int num_devices = acc_get_num_devices(acc_device_default);
    if (num_devices < 1) {
        // fail if no devices found or initialization did not occur correctly
        err = 1;
    } else {
        // Optionally, if devices are found, ensure they can be set without errors
        for (int i = 0; i < num_devices; ++i) {
            acc_set_device_num(i, acc_device_default);
            if (acc_get_device_num(acc_device_default) != i) {
                // If the device couldn't be set correctly, an error has occurred
                err = 1;
            }
        }
    }

    // Finalize the OpenACC runtime to clean up
    acc_shutdown(acc_device_default);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}