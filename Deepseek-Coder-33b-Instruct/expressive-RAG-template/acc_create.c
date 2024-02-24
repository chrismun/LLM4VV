#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *host_data = (int*)malloc(SIZE * sizeof(int));
    int *device_data;
    int i;

    // Initialize host data
    for(i = 0; i < SIZE; i++) {
        host_data[i] = i;
    }

    // Create device data
    #pragma acc data copyin(host_data[0:SIZE]) create(device_data[0:SIZE])
    {
        // Copy data from host to device
        #pragma acc update device(device_data[0:SIZE])

        // Check if data is correctly copied
        for(i = 0; i < SIZE; i++) {
            if(host_data[i] != device_data[i]) {
                printf("Data is not correctly copied at index %d\n", i);
                return 1; // Return non-zero to indicate failure
            }
        }
    }

    printf("Data is correctly copied\n");
    return 0; // Return zero to indicate success
}