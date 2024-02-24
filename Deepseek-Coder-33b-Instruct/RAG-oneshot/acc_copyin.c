#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 10

int main() {
    int *host_array = (int*)malloc(SIZE * sizeof(int));
    int *device_array;

    // Initialize host array
    for(int i = 0; i < SIZE; i++) {
        host_array[i] = i;
    }

    // Allocate memory on the device
    device_array = (int*)acc_malloc(SIZE * sizeof(int));

    // Copy data from host to device
    #pragma acc data copyin(host_array[0:SIZE])
    {
        #pragma acc kernels
        {
            for(int i = 0; i < SIZE; i++) {
                device_array[i] = host_array[i];
            }
        }
    }

    // Verify the copy
    for(int i = 0; i < SIZE; i++) {
        printf("device_array[%d] = %d\n", i, device_array[i]);
    }

    // Free memory
    free(host_array);
    acc_free(device_array);

    return 0;
}