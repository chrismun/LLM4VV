#include <openacc.h>

int main() {
    int failcode = 0;

    // Create a host array
    int host_array[10];

    // Create a device array
    int device_array[10];

    // Initialize the host array
    for (int i = 0; i < 10; i++) {
        host_array[i] = i;
    }

    // Copy the host array to the device array
    #pragma acc host_data use_device(device_array)
    {
        #pragma acc parallel
        {
            for (int i = 0; i < 10; i++) {
                device_array[i] = host_array[i];
            }
        }
    }

    // Check that the device array is equal to the host array
    for (int i = 0; i < 10; i++) {
        if (device_array[i] != host_array[i]) {
            failcode = 1;
            break;
        }
    }

    return failcode;
}