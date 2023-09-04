#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test_acc_on_device() {
    int err = 0;
    int device_id = 0;
    int num_devices = 0;
    int device_type = 0;
    int device_vendor = 0;
    int device_name_len = 0;
    char device_name[256];

    // Get the number of devices
    num_devices = acc_get_num_devices();
    if (num_devices <= 0) {
        fprintf(stderr, "No OpenACC devices found\n");
        return 1;
    }

    // Get the device ID
    device_id = acc_get_device_id();
    if (device_id < 0 || device_id >= num_devices) {
        fprintf(stderr, "Invalid OpenACC device ID: %d\n", device_id);
        return 1;
    }

    // Get the device type
    device_type = acc_get_device_type(device_id);
    if (device_type != ACC_DEVICE_TYPE_GPU) {
        fprintf(stderr, "Invalid OpenACC device type: %d\n", device_type);
        return 1;
    }

    // Get the device vendor
    device_vendor = acc_get_device_vendor(device_id);
    if (device_vendor != ACC_DEVICE_VENDOR_NVIDIA) {
        fprintf(stderr, "Invalid OpenACC device vendor: %d\n", device_vendor);
        return 1;
    }

    // Get the device name
    device_name_len = acc_get_device_name(device_id, device_name, sizeof(device_name));
    if (device_name_len <= 0) {
        fprintf(stderr, "Failed to get OpenACC device name\n");
        return 1;
    }

    // Print the device information
    printf("OpenACC device ID: %d\n", device_id);
    printf("OpenACC device type: %s\n", acc_get_device_type_string(device_type));
    printf("OpenACC device vendor: %s\n", acc_get_device_vendor_string(device_vendor));
    printf("OpenACC device name: %s\n", device_name);

    return 0;
}

int main() {
    int failcode = 0;
    int failed;

    failed = test_acc_on_device();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}