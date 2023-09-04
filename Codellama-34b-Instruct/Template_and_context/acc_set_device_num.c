#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_TYPE_CPU);

    // Set the device number to 0
    acc_set_device_num(0, ACC_DEVICE_TYPE_CPU);

    // Check that the device number is set correctly
    if (acc_get_device_num() != 0) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}