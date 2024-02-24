#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *host_data, *device_data;
    int i;

    // Allocate memory on the host
    host_data = (int*)malloc(SIZE * sizeof(int));
    if(host_data == NULL) {
        fprintf(stderr, "Failed to allocate host memory\n");
        return 1;
    }

    // Allocate memory on the device
    device_data = (int*)acc_malloc(SIZE * sizeof(int));
    if(device_data == NULL) {
        fprintf(stderr, "Failed to allocate device memory\n");
        return 1;
    }

    // Initialize host data
    for(i = 0; i < SIZE; i++) {
        host_data[i] = i;
    }

    // Copy data from host to device
    #pragma acc data copyin(host_data[0:SIZE]) copyout(device_data[0:SIZE])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for(i = 0; i < SIZE; i++) {
                device_data[i] = host_data[i];
            }
        }
    }

    // Verify the data
    for(i = 0; i < SIZE; i++) {
        if(host_data[i] != device_data[i]) {
            fprintf(stderr, "Data verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Data copied successfully from host to device\n");

    // Free memory
    free(host_data);
    acc_free(device_data);

    return 0;
}