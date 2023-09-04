#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc set device type
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != ACC_DEVICE_TYPE_GPU) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}