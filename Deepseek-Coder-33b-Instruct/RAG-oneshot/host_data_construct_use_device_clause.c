#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *host_array = (int*)malloc(SIZE * sizeof(int));
    int *device_array;

    // Initialize host array
    for(int i = 0; i < SIZE; i++) {
        host_array[i] = i;
    }

    // Allocate device memory
    device_array = (int*)acc_malloc(SIZE * sizeof(int));

    // Copy data to device
    #pragma acc data copyin(host_array[0:SIZE])
    {
        // Use device clause to pass device address of array to optimized procedure
        #pragma acc kernels use_device(device_array)
        {
            int i;
            #pragma acc loop
            for(i = 0; i < SIZE; i++) {
                device_array[i] = host_array[i];
            }
        }
    }

    // Verify the use of the device address
    for(int i = 0; i < SIZE; i++) {
        if(device_array[i] != host_array[i]) {
            printf("Error: use_device clause not working as expected\n");
            return 1;
        }
    }

    printf("Success: use_device clause working as expected\n");

    // Free memory
    free(host_array);
    acc_free(device_array);

    return 0;
}