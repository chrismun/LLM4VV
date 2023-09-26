#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the device type
    int device_type = 0;

    // Create a loop construct with the device_type clause
    #pragma acc loop device_type(device_type)
    for (int i = 0; i < 10; i++) {
        // Do some work on the device
        #pragma acc parallel loop device_type(device_type)
        for (int j = 0; j < 10; j++) {
            // Do some work on the device
        }
    }

    // Check if the device type is correct
    if (device_type != 0) {
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