#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_DEVICES 4

int main() {
    int num_devices;
    int device_num;

    // Get the number of devices
    num_devices = acc_get_num_devices();

    // Check if the number of devices is valid
    if (num_devices < 1 || num_devices > NUM_DEVICES) {
        printf("Invalid number of devices: %d\n", num_devices);
        return 1;
    }

    // Get the device number
    device_num = acc_get_device_num();

    // Check if the device number is valid
    if (device_num < 0 || device_num >= num_devices) {
        printf("Invalid device number: %d\n", device_num);
        return 1;
    }

    // Print the device number
    printf("Device number: %d\n", device_num);

    return 0;
}