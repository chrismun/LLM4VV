#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.00001

int test_acc_get_property(int device_type, int device_id, int property_type, int property_id, int expected_value) {
    int err = 0;
    int actual_value;

    // Set the device type and device ID
    acc_set_device_type(device_type);
    acc_set_device_id(device_id);

    // Get the property value
    actual_value = acc_get_property(property_type, property_id);

    // Check if the actual value matches the expected value
    if (actual_value != expected_value) {
        err = 1;
        printf("Error: Expected value for property %d (%s) is %d, but got %d\n", property_id, acc_get_property_string(property_type, property_id), expected_value, actual_value);
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Test the acc get property clause for different device types and properties
    failed = test_acc_get_property(ACC_DEVICE_TYPE_GPU, 0, ACC_PROPERTY_TYPE_MEMORY, ACC_PROPERTY_MEMORY_SIZE, 1024);
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    failed = test_acc_get_property(ACC_DEVICE_TYPE_CPU, 0, ACC_PROPERTY_TYPE_MEMORY, ACC_PROPERTY_MEMORY_SIZE, 1024);
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    failed = test_acc_get_property(ACC_DEVICE_TYPE_ACCELERATOR, 0, ACC_PROPERTY_TYPE_MEMORY, ACC_PROPERTY_MEMORY_SIZE, 1024);
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    failed = test_acc_get_property(ACC_DEVICE_TYPE_GPU, 0, ACC_PROPERTY_TYPE_MAX_THREADS, ACC_PROPERTY_MAX_THREADS, 1024);
    if (failed != 0) {
        failcode = failcode + (1 << 3);
    }

    failed = test_acc_get_property(ACC_DEVICE_TYPE_CPU, 0, ACC_PROPERTY_TYPE_MAX_THREADS, ACC_PROPERTY_MAX_THREADS, 1024);
    if (failed != 0) {
        failcode = failcode + (1 << 4);
    }

    failed = test_acc_get_property(ACC_DEVICE_TYPE_ACCELERATOR, 0, ACC_PROPERTY_TYPE_MAX_THREADS, ACC_PROPERTY_MAX_THREADS, 1024);
    if (failed != 0) {
        failcode = failcode + (1 << 5);
    }

    return failcode;
}