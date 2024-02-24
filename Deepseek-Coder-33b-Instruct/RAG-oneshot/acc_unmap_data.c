#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *host_data = (int*)malloc(SIZE * sizeof(int));
    int *device_data = NULL;

    // Initialize host data
    for(int i = 0; i < SIZE; i++) {
        host_data[i] = i;
    }

    // Map host data to device
    #pragma acc data copyin(host_data[0:SIZE])
    {
        device_data = host_data;
    }

    // Unmap device data from host
    acc_unmap_data(host_data);

    // Check if device data is unmapped
    if(device_data == NULL) {
        printf("Device data is unmapped successfully.\n");
    } else {
        printf("Device data is not unmapped.\n");
    }

    free(host_data);

    return 0;
}