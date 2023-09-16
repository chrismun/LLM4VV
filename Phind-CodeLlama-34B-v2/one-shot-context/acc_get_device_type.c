#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    acc_device_t device_type;

    device_type = acc_get_device_type();

    if (device_type == acc_device_none) {
        printf("Device type has not been selected yet.\n");
    } else if (device_type == acc_device_default) {
        printf("Device type is set to default.\n");
    } else if (device_type == acc_device_host) {
        printf("Device type is set to host.\n");
    } else if (device_type == acc_device_not_host) {
        printf("Device type is set to a non-host device.\n");
    } else if (device_type == acc_device_nvidia) {
        printf("Device type is set to NVIDIA GPU.\n");
    } else {
        printf("Unknown device type.\n");
    }

    return 0;
}