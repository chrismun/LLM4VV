#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *host_array = (int*)malloc(SIZE * sizeof(int));
    int *device_array = (int*)malloc(SIZE * sizeof(int));

    // Initialize host array
    for(int i = 0; i < SIZE; i++) {
        host_array[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_array[0:SIZE]) copyout(device_array[0:SIZE])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for(int i = 0; i < SIZE; i++) {
                device_array[i] = host_array[i];
            }
        }
    }

    // Verify the copy
    for(int i = 0; i < SIZE; i++) {
        if(host_array[i] != device_array[i]) {
            printf("Error: host_array[%d] = %d, device_array[%d] = %d\n", i, host_array[i], i, device_array[i]);
            return 1;
        }
    }

    printf("Success: Data copied correctly from device to host.\n");

    free(host_array);
    free(device_array);

    return 0;
}