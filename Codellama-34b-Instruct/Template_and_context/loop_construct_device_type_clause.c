#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device_type clause with a random device type
    int device_type = rand() % 2;
    acc_set_device_type(device_type);

    // Create a loop construct with the device_type clause
    #pragma acc loop device_type(device_type)
    for (int i = 0; i < 10; i++) {
        // Do some work
    }

    // Check if the device type was set correctly
    if (acc_get_device_type() != device_type) {
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