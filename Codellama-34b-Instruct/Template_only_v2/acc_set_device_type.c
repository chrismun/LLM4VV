#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_TYPE_CPU);

    // Create a device
    acc_device_t device = acc_get_device(0);

    // Check that the device type is CPU
    if (device->type != ACC_DEVICE_TYPE_CPU) {
        err = 1;
    }

    // Set the device type to GPU
    acc_set_device_type(ACC_DEVICE_TYPE_GPU);

    // Create a device
    device = acc_get_device(0);

    // Check that the device type is GPU
    if (device->type != ACC_DEVICE_TYPE_GPU) {
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}