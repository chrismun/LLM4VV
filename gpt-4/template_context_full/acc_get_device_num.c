#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

// T1: acc get device num, V: 2.0-2.7
int test_acc_get_device_num() {
    int deviceNum;
    int err = 0;

    // Initialize the random seed
    srand(SEED);

    // Check the device number
    deviceNum = acc_get_device_num(acc_device_default);
    if(deviceNum < 0) {
        printf("[Test] Error! Device number: %d\n", deviceNum);
        err = 1;
    } 

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    // Loop through and run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_acc_get_device_num();
    }
    // If any of the tests failed, increment the fail code
    if (failed != 0) {
        failcode += (1 << 0);
    }

    return failcode;
}