#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc shutdown
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        acc_shutdown();
        if (acc_get_device_type() != ACC_DEVICE_NONE) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}