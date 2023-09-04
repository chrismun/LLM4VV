#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Initialize the runtime
    acc_init(acc_device_default);

    // Create a device
    acc_device_t dev_type = acc_device_default;
    int dev_num = acc_get_device_num(dev_type);

    // Shut down the device
    acc_shutdown(dev_type);

    // Check that the device is no longer available
    if (acc_get_device_num(dev_type) != -1) {
        err = 1;
    }

    // Free the device
    acc_free(dev_num);

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