#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data clause with an invalid data type
    int data[10];
    #pragma acc data copy(data)
    {
        // Attempt to copy data to the device
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            data[i] = i;
        }
    }

    // Check for errors
    if (acc_get_device_type() == acc_device_host) {
        // Host device, check for errors
        if (acc_get_num_devices() == 0) {
            // No devices found, return error
            err = 1;
        } else {
            // Devices found, check for errors
            for (int i = 0; i < acc_get_num_devices(); i++) {
                if (acc_get_device_type(i) == acc_device_host) {
                    // Host device, check for errors
                    if (acc_get_device_error(i) != 0) {
                        // Error found, return error
                        err = 1;
                    }
                }
            }
        }
    } else {
        // Device device, check for errors
        if (acc_get_device_error() != 0) {
            // Error found, return error
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