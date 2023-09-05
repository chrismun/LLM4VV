#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc get property
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_property(x, ACC_PROPERTY_DEVICE_TYPE);
        if (device_type != ACC_DEVICE_TYPE_GPU) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: acc get property
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_property(x, ACC_PROPERTY_DEVICE_TYPE);
        if (device_type != ACC_DEVICE_TYPE_CPU) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    // Test 3: acc get property
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_property(x, ACC_PROPERTY_DEVICE_TYPE);
        if (device_type != ACC_DEVICE_TYPE_ACCELERATOR) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    // Test 4: acc get property
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_property(x, ACC_PROPERTY_DEVICE_TYPE);
        if (device_type != ACC_DEVICE_TYPE_HOST) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 3);
    }

    // Test 5: acc get property
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_property(x, ACC_PROPERTY_DEVICE_TYPE);
        if (device_type != ACC_DEVICE_TYPE_UNKNOWN) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 4);
    }

    return failcode;
}