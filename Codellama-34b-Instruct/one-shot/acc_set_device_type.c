#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc set device type
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != acc_device_default) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: acc set device type with acc_device_default
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != acc_device_default) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    // Test 3: acc set device type with acc_device_host
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != acc_device_host) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    // Test 4: acc set device type with acc_device_not_host
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != acc_device_not_host) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 3);
    }

    // Test 5: acc set device type with acc_device_gpu
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != acc_device_gpu) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 4);
    }

    // Test 6: acc set device type with acc_device_fpga
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != acc_device_fpga) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 5);
    }

    // Test 7: acc set device type with acc_device_mic
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != acc_device_mic) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 6);
    }

    // Test 8: acc set device type with acc_device_dsp
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != acc_device_dsp) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 7);
    }

    // Test 9: acc set device type with acc_device_nvidia
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != acc_device_nvidia) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 8);
    }

    // Test 10: acc set device type with acc_device_amd
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int device_type = acc_get_device_type();
        if (device_type != acc_device_amd) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 9);
    }

    return failcode;
}