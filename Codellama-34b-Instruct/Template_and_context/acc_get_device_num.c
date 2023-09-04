#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

int acc_get_device_num(acc_device_t dev_type) {
    int num_devices = acc_get_num_devices(dev_type);
    if (num_devices == 0) {
        return -1;
    }

    int current_device = acc_get_current_device();
    if (current_device == -1) {
        return -1;
    }

    return current_device;
}

int main() {
    int num_devices = acc_get_num_devices(ACC_DEVICE_TYPE_ALL);
    if (num_devices == 0) {
        printf("No devices found\n");
        return 1;
    }

    int current_device = acc_get_device_num(ACC_DEVICE_TYPE_ALL);
    if (current_device == -1) {
        printf("No devices of type ACC_DEVICE_TYPE_ALL found\n");
        return 1;
    }

    printf("Current device number: %d\n", current_device);

    return 0;
}