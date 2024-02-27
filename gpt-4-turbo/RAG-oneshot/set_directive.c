#include <stdio.h>
#include <openacc.h>

int validate_default_async() {
    int original = acc_get_default_async();

    // Set default_async to a new value
    #pragma acc set default_async(5)
    int new_async = acc_get_default_async();

    // Restore original value
    #pragma acc set default_async(original)
    return original != new_async ? new_async : -1; // Return new_async if change was successful, else -1
}

int validate_device_num() {
    int original = acc_get_device_num(acc_device_none);

    // Assuming at least 2 devices are present, switch to another device
    #pragma acc set device_num(1)
    int new_device = acc_get_device_num(acc_device_none);

    // Restore original device
    #pragma acc set device_num(original)
    return original != new_device ? new_device : -1; // Return new_device if change was successful, else -1
}

int main() {
    if (acc_get_num_devices(acc_device_not_host) <= 0) {
        printf("No accelerator devices found.\n");
        return -1;
    }
    int async_valid = validate_default_async();
    int device_valid = validate_device_num();

    if(async_valid != -1) {
        printf("Default async validation successful, new queue ID: %d\n", async_valid);
    } else {
        printf("Default async validation failed. Ensure the system supports asynchronous operations.\n");
    }

    if(device_valid != -1) {
        printf("Device num validation successful, new device num: %d\n", device_valid);
    } else {
        printf("Device num validation failed. Ensure the system has at least two devices.\n");
    }

    return 0;
}