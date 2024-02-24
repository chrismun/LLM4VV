#include <stdio.h>
#include <openacc.h>

int main() {
    acc_device_t device_type = acc_get_device_type();
    printf("Current device type: %d\n", device_type);

    acc_set_device_type(acc_device_nvidia);
    device_type = acc_get_device_type();
    printf("Device type after setting: %d\n", device_type);

    if (device_type == acc_device_nvidia) {
        printf("Device type successfully set to NVIDIA\n");
    } else {
        printf("Failed to set device type\n");
    }

    return 0;
}