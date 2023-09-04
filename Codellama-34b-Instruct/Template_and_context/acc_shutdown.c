#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    // Create a new device
    acc_device_t dev_type = acc_device_default;
    int dev_num = acc_get_device_num(dev_type);

    // Shut down the device
    acc_shutdown(dev_type);

    // Check that the device is no longer available
    if (acc_get_device_num(dev_type) != -1) {
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();
        if (failed != 0){
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}