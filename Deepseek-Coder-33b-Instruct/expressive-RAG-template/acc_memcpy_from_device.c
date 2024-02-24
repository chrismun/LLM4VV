#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *host_data = (int*)malloc(SIZE * sizeof(int));
    int *device_data = (int*)malloc(SIZE * sizeof(int));

    // Initialize host data
    for(int i = 0; i < SIZE; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    #pragma acc enter data copyin(device_data[0:SIZE])
    #pragma acc update device(device_data[0:SIZE])

    // Copy data from device to host
    #pragma acc update self(host_data[0:SIZE])

    // Verify the data
    for(int i = 0; i < SIZE; i++) {
        if(host_data[i] != i) {
            printf("Data verification failed at index %d\n", i);
            return 1; // Return non-zero to indicate failure
        }
    }

    printf("Data verification passed\n");
    return 0; // Return zero to indicate success
}