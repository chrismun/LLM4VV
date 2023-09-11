#include <iostream>
#include <cstdlib>
#include <cmath>

#include "acc_testsuite.h"

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc async test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = test1();
        if (err != 0) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}

int test1() {
    int err = 0;
    srand(SEED);

    // Create an async queue
    int async_queue = acc_async_queue_create();

    // Create a device
    int dev_num = acc_device_create();

    // Create a data array
    int data[10];
    for (int i = 0; i < 10; ++i) {
        data[i] = i;
    }

    // Copy data to device
    acc_copy_to_device(data, 10, dev_num);

    // Launch a kernel on the device
    acc_launch_kernel(dev_num, async_queue, data, 10);

    // Wait for the kernel to complete
    acc_async_test(async_queue);

    // Check the result
    for (int i = 0; i < 10; ++i) {
        if (data[i] != i * 2) {
            err = 1;
            break;
        }
    }

    // Clean up
    acc_async_queue_destroy(async_queue);
    acc_device_destroy(dev_num);

    return err;
}