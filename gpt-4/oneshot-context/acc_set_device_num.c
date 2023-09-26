#include <stdio.h>
#include <openacc.h>

int main() {
    // Get the total number of devices available 
    int numDevices = acc_get_num_devices(acc_device_default);
    
    printf("The total number of devices available: %d\n", numDevices);

    for(int i = 0; i < numDevices; i++) {
        // Set each available device and verify the selected device
        acc_set_device_num(i, acc_device_default);

        // Retrieve the current device number
        int currentDevice = acc_get_device_num(acc_device_default);
    
        if(currentDevice != i) {
            printf("Failed to set device to %d, acc_set_device_num not working properly\n", i);
            return 1;
        }

        printf("Currently executing on device: %d\n", currentDevice);
    }

    // Reset to default behaviour
    acc_set_device_num(-1, acc_device_default);
  
    printf("acc_set_device_num passed all tests\n");
    
    return 0;