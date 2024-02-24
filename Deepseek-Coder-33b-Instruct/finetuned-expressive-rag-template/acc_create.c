#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 10

int main() {
    int *host_array = (int*)malloc(SIZE * sizeof(int));
    int *device_array;
    int i;

    // Initialize host array
    for (i = 0; i < SIZE; i++) {
        host_array[i] = i;
    }

    // Create device array
    #pragma acc data copyin(host_array[0:SIZE]) create(device_array[0:SIZE])
    {
        #pragma acc parallel loop
        for (i = 0; i < SIZE; i++) {
            device_array[i] = host_array[i];
        }
    }

    // Check if device array is correct
    for (i = 0; i < SIZE; i++) {
        if (device_array[i] != host_array[i]) {
            printf("Error: device_array[%d] = %d, expected %d\n", i, device_array[i], host_array[i]);
            return 1; // Return non-zero to indicate failure
        }
    }

    printf("Test passed\n");
    return 0; // Return zero to indicate success
}