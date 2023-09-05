#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int main() {
    int failcode = 0;
    int failed;

    // Test acc_shutdown
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        acc_shutdown(acc_device_host);
        if (acc_get_device_type() != acc_device_host) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test acc_shutdown_device
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        acc_shutdown_device(0, acc_device_host);
        if (acc_get_device_type(0) != acc_device_host) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    return failcode;
}