#include "acc_testsuite.h"

// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the device
    acc_init(acc_device_default);

    // Check if the device is initialized
    if (acc_get_device_type() != acc_device_default) {
        err = 1;
    }

    // Check if the device is shut down
    if (acc_get_device_state() != acc_device_shutdown) {
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test
    failed = test1();

    // Check if the test failed
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}