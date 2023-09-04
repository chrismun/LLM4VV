#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

int main() {
    int num_devices;
    acc_get_num_devices(&num_devices);

    if (num_devices < 1) {
        printf("Error: No OpenACC devices found.\n");
        return 1;
    }

    printf("Number of OpenACC devices: %d\n", num_devices);

    for (int i = 0; i < num_devices; i++) {
        acc_device_t device;
        acc_get_device(&device, i);

        printf("Device %d: %s\n", i, acc_get_device_name(device));
    }

    return 0;
}