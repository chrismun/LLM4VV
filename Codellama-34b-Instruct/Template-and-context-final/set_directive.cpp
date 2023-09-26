#include "acc_testsuite.h"

// T1:set directive,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Set the default asynchronous queue to the initial value
    #pragma acc set default_async(acc_async_default)

    // Set the device number to a random value
    int device_num = rand() % 10;
    #pragma acc set device_num(device_num)

    // Set the device type to a random value
    int device_type = rand() % 2;
    #pragma acc set device_type(device_type)

    // Set the default asynchronous queue to the initial value
    #pragma acc set default_async(acc_async_default)

    // Set the device number to a random value
    device_num = rand() % 10;
    #pragma acc set device_num(device_num)

    // Set the device type to a random value
    device_type = rand() % 2;
    #pragma acc set device_type(device_type)

    // Check that the default asynchronous queue is set to the initial value
    if (acc_default_async_var != acc_async_default) {
        err = 1;
    }

    // Check that the device number is set to the random value
    if (acc_current_device_num_var != device_num) {
        err = 1;
    }

    // Check that the device type is set to the random value
    if (acc_current_device_type_var != device_type) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}