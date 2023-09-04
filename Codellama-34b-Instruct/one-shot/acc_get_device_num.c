#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int num_devices;
    acc_get_device_num(&num_devices);

    if (num_devices == 0) {
        printf("No OpenACC devices found.\n");
        return 1;
    }

    printf("Found %d OpenACC devices.\n", num_devices);

    for (int i = 0; i < num_devices; i++) {
        acc_device_t device;
        acc_get_device(&device, i);

        printf("Device %d: %s\n", i, device.name);
    }

    return 0;
}