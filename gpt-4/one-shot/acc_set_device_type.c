#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Set the device type to 'acc_device_host', equivalent to calling acc_set_device_type(acc_device_host)
#pragma acc_init(device_type = acc_device_host)

// Set the device type to 'acc_device_nvidia', equivalent to calling acc_set_device_type(acc_device_nvidia)
#pragma acc_init(device_type = acc_device_nvidia)

int main() {
    int deviceType = acc_get_device_type();

    switch(deviceType) {
        case acc_device_host: 
            printf("The device type is acc_device_host\n");
            break;
        case acc_device_nvidia: 
            printf("The device type is acc_device_nvidia\n");
            break;
        default: 
            printf("Unknown device type\n");
            return 1;
    }
    return 0;
}