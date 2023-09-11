#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Test if the code is running on the host
    if (acc_on_device(acc_device_host) == 1) {
        printf("Running on host\n");
    } else {
        printf("Not running on host\n");
        err = 1;
    }

    // Test if the code is running on a device
    if (acc_on_device(acc_device_not_host) == 1) {
        printf("Running on device\n");
    } else {
        printf("Not running on device\n");
        err = 1;
    }

    // Test if the code is running on a specific device
    if (acc_on_device(acc_device_default) == 1) {
        printf("Running on default device\n");
    } else {
        printf("Not running on default device\n");
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}