#include <stdio.h>
#include <stdlib.h>
#include <accelerator.h>

#define NUM_TEST_CALLS 10
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Get the device type
    int device_type = acc_get_device_type();

    // Check if the device type is valid
    if (device_type < 0 || device_type > 3) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}