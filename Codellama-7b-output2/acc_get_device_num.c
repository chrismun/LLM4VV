#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <accelerator.h>

#define NUM_DEVICES 2

int main() {
    int device_num;
    int num_devices;

    // Get the number of devices
    num_devices = acc_get_num_devices();

    // Check if the number of devices is greater than 0
    if (num_devices <= 0) {
        printf("Error: The number of devices is not greater than 0\n");
        return 1;
    }

    // Get the device number
    device_num = acc_get_device_num();

    // Check if the device number is within the range of the number of devices
    if (device_num < 0 || device_num >= num_devices) {
        printf("Error: The device number is not within the range of the number of devices\n");
        return 1;
    }

    // Print the device number
    printf("Device number: %d\n", device_num);

    return 0;
}