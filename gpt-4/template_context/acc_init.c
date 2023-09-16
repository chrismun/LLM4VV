#include "openacc.h"  // OpenACC library
#include <stdio.h>    // Standard I/O libarary

int main() {

    // First, check if the device is not initialized
    if (acc_get_device_type() == acc_device_none) {
        printf("No device is initialized.\n");
    }   

    // Now, try to initialize the device
    acc_init(acc_device_default);

    // Check the device type again
    acc_device_t deviceType = acc_get_device_type();

    // If the device has been initialized, it should not be 'acc_device_none'
    if (deviceType != acc_device_none) {
        printf("The device is initialized successfully.\n");
    } else {
        printf("Device initialization failed.\n");
        return -1;  // Return error
    }

    // Check device number
    int deviceNum = acc_get_device_num(deviceType);
    printf("Device number: %d\n", deviceNum);

    return 0;  // Return success
}