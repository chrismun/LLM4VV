#include <stdio.h>
#include <openacc.h>

#define SIZE 1024

// Custom function to check if the OpenACC device is available and can be initialized
int check_device_initialization() {
    int isAvailable = 0; // Flag to check device availability

    // Try to initialize a specific device type (for example, GPU)
    #pragma acc init device_type(nvidia) if(acc_get_num_devices(acc_device_nvidia) > 0)

    // Check if the device is available and initialization was successful
    #pragma acc parallel num_gangs(1) reduction(+:isAvailable)
    {
        isAvailable += 1;
    }

    return isAvailable;
}

int main() {
    if (!acc_get_num_devices(acc_device_nvidia)) {
        printf("No NVIDIA GPU device available.\n");
        return 1;
    }

    if (check_device_initialization()) {
        printf("OpenACC device was successfully initialized.\n");
    } else {
        printf("Failed to initialize OpenACC device.\n");
    }
    return 0;
}