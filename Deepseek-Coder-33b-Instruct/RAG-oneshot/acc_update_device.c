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
    #pragma acc data copyin(host_data[0:SIZE]) copyout(device_data[0:SIZE])
    {
        #pragma acc kernels
        for(int i = 0; i < SIZE; i++) {
            device_data[i] = host_data[i];
        }
    }

    // Verify data in device
    for(int i = 0; i < SIZE; i++) {
        if(device_data[i] != i) {
            printf("Data verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Data verification successful\n");

    // Update device data
    #pragma acc update device(device_data[0:SIZE])

    // Verify updated data in device
    for(int i = 0; i < SIZE; i++) {
        if(device_data[i] != i) {
            printf("Data update verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Data update verification successful\n");

    // Update host data
    #pragma acc update self(host_data[0:SIZE])

    // Verify updated data in host
    for(int i = 0; i < SIZE; i++) {
        if(host_data[i] != i) {
            printf("Data update verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Data update verification successful\n");

    free(host_data);
    free(device_data);

    return 0;
}