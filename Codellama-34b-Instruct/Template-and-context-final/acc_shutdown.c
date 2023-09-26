#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device
    acc_device_t dev_type = acc_device_default;
    int dev_num = acc_get_device_num(dev_type);
    if (dev_num < 0) {
        fprintf(stderr, "Failed to get device number for device type %d\n", dev_type);
        return 1;
    }

    // Shut down the device
    acc_shutdown(dev_type);

    // Check that the device is no longer available
    if (acc_get_device_num(dev_type) >= 0) {
        fprintf(stderr, "Device %d is still available after shutdown\n", dev_num);
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