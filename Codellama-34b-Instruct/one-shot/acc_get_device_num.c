#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int num_devices;
    int device_num;

    // Get the number of devices
    num_devices = acc_get_num_devices();

    // Check that the number of devices is greater than 0
    if (num_devices <= 0) {
        printf("Error: No devices found.\n");
        return 1;
    }

    // Get the device number
    device_num = acc_get_device_num();

    // Check that the device number is valid
    if (device_num < 0 || device_num >= num_devices) {
        printf("Error: Invalid device number.\n");
        return 1;
    }

    // Print the device number
    printf("Device number: %d\n", device_num);

    return 0;
}