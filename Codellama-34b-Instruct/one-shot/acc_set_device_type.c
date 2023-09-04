#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_acc_set_device_type(void) {
    int err = 0;
    int device_type = acc_get_device_type();

    // Set the device type to GPU
    acc_set_device_type(ACC_DEVICE_TYPE_GPU);

    // Check if the device type is set correctly
    if (acc_get_device_type() != ACC_DEVICE_TYPE_GPU) {
        err++;
    }

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_TYPE_CPU);

    // Check if the device type is set correctly
    if (acc_get_device_type() != ACC_DEVICE_TYPE_CPU) {
        err++;
    }

    // Restore the original device type
    acc_set_device_type(device_type);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure correctness
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test_acc_set_device_type();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}