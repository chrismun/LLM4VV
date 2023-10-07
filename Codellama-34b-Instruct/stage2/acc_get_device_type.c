#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

int test1() {
    int err = 0;
    srand(SEED);

    // Get the current device type
    acc_device_t device_type = acc_get_device_type();

    // Check if the device type is supported
    if (device_type == acc_device_none) {
        printf("Device type not supported\n");
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