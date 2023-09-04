#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 100

int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the runtime for the specified device type and device number
    acc_init(ACC_DEVICE_TYPE_GPU);
    acc_init_device(0, ACC_DEVICE_TYPE_GPU);

    // Check that the device is initialized
    if (acc_get_device_type() != ACC_DEVICE_TYPE_GPU || acc_get_device_num() != 0) {
        err = 1;
    }

    // Shut down the device
    acc_shutdown();

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();
        if (failed != 0){
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}