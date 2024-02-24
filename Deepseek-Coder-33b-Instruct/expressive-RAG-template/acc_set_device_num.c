#include <stdio.h>
#include <openacc.h>

int main() {
    int err = 0;
    int device_count = acc_get_num_devices(acc_device_nvidia);

    if (device_count < 1) {
        printf("No NVIDIA devices found\n");
        return 1;
    }

    printf("Number of NVIDIA devices: %d\n", device_count);

    for (int i = 0; i < device_count; i++) {
        acc_set_device_num(i, acc_device_nvidia);
        printf("Setting device number to %d\n", i);
        if (acc_get_device_num(acc_device_nvidia) != i) {
            printf("Failed to set device number to %d\n", i);
            err = 1;
        }
    }

    return err;
}