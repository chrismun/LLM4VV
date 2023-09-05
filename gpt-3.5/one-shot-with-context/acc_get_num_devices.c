#include <stdio.h>
#include <openacc.h>

int main() {
    // Get the number of available devices of type acc_device_t
    int numDevices = acc_get_num_devices(acc_device_default);
    
    if (numDevices > 0) {
        printf("Number of devices: %d\n", numDevices);
    }
    else {
        printf("No devices of the specified type are available.\n");
    }
    
    return 0;
}