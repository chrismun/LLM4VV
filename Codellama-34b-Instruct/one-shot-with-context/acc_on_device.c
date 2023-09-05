#include <openacc.h>

int main() {
    int failcode = 0;

    // Check if the program is running on the host
    if (acc_on_device(acc_device_host)) {
        // If the program is running on the host, check if the device type is supported
        if (acc_get_device_type() == acc_device_host) {
            // If the device type is supported, check if the device is available
            if (acc_get_device_count(acc_device_host) > 0) {
                // If the device is available, check if the device is the default device
                if (acc_get_device() == acc_device_host) {
                    // If the device is the default device, print a message
                    printf("The program is running on the host with a supported device type and the device is the default device.\n");
                } else {
                    // If the device is not the default device, print a message
                    printf("The program is running on the host with a supported device type, but the device is not the default device.\n");
                }
            } else {
                // If the device is not available, print a message
                printf("The program is running on the host with a supported device type, but the device is not available.\n");
            }
        } else {
            // If the device type is not supported, print a message
            printf("The program is running on the host with an unsupported device type.\n");
        }
    } else {
        // If the program is not running on the host, check if the device type is supported
        if (acc_get_device_type() == acc_device_not_host) {
            // If the device type is supported, check if the device is available
            if (acc_get_device_count(acc_device_not_host) > 0) {
                // If the device is available, check if the device is the default device
                if (acc_get_device() == acc_device_not_host) {
                    // If the device is the default device, print a message
                    printf("The program is running on a device with a supported device type and the device is the default device.\n");
                } else {
                    // If the device is not the default device, print a message
                    printf("The program is running on a device with a supported device type, but the device is not the default device.\n");
                }
            } else {
                // If the device is not available, print a message
                printf("The program is running on a device with a supported device type, but the device is not available.\n");
            }
        } else {
            // If the device type is not supported, print a message
            printf("The program is running on a device with an unsupported device type.\n");
        }
    }

    return failcode;
}