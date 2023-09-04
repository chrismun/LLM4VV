#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_DEVICES 4
#define DEVICE_NUM 1

int main() {
    int i, j, k;
    int num_devices;
    int device_num;
    int *devices;
    int *device_nums;

    // Initialize the devices and device numbers
    devices = (int *)malloc(NUM_DEVICES * sizeof(int));
    device_nums = (int *)malloc(NUM_DEVICES * sizeof(int));
    for (i = 0; i < NUM_DEVICES; i++) {
        devices[i] = i;
        device_nums[i] = i;
    }

    // Set the device number
    acc_set_device_num(DEVICE_NUM);

    // Get the number of devices and the device number
    num_devices = acc_get_num_devices();
    device_num = acc_get_device_num();

    // Check if the device number is set correctly
    if (device_num != DEVICE_NUM) {
        printf("Error: Device number is not set correctly.\n");
        return 1;
    }

    // Check if the number of devices is correct
    if (num_devices != NUM_DEVICES) {
        printf("Error: Number of devices is not correct.\n");
        return 1;
    }

    // Check if the device numbers are correct
    for (i = 0; i < NUM_DEVICES; i++) {
        if (device_nums[i] != devices[i]) {
            printf("Error: Device number %d is not correct.\n", i);
            return 1;
        }
    }

    // Free the memory
    free(devices);
    free(device_nums);

    return 0;
}