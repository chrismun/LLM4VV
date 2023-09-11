#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Set the device number to a random value
    int dev_num = rand() % 10;

    // Set the device type to a random value
    acc_device_t dev_type = (acc_device_t)rand() % 2;

    // Call acc_set_device_num with the random device number and type
    acc_set_device_num(dev_num, dev_type);

    // Check that the device number was set correctly
    if (acc_get_device_num() != dev_num) {
        err = 1;
    }

    // Check that the device type was set correctly
    if (acc_get_device_type() != dev_type) {
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