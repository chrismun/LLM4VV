#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc/acc_runtime.h>

int main() {
    int num_devices = acc_get_num_devices(ACC_DEVICE_TYPE_ALL);
    int num_devices_supported = acc_get_num_devices(ACC_DEVICE_TYPE_SUPPORTED);
    int num_devices_unsupported = acc_get_num_devices(ACC_DEVICE_TYPE_UNSUPPORTED);

    printf("Number of devices: %d\n", num_devices);
    printf("Number of devices supported: %d\n", num_devices_supported);
    printf("Number of devices unsupported: %d\n", num_devices_unsupported);

    for (int i = 0; i < num_devices; i++) {
        acc_device_t device_type = acc_get_device_type(i);
        int device_num = acc_get_device_num(device_type);
        printf("Device %d: type = %s, num = %d\n", i, acc_get_device_type_string(device_type), device_num);
    }

    return 0;
}