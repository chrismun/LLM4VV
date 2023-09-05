#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

int main() {
    int num_devices;
    acc_device_t dev_type;

    // Get the number of available devices of the given type
    num_devices = acc_get_num_devices(dev_type);

    // Check if the number of devices is valid
    if (num_devices < 1) {
        printf("Error: No devices available of type %d\n", dev_type);
        return 1;
    }

    // Print the number of devices
    printf("Number of devices available: %d\n", num_devices);

    return 0;
}