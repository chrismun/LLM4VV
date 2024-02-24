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

    // Copy host array to device
    #pragma acc data copyin(host_array[0:SIZE]) copyout(device_array[0:SIZE])
    {
        #pragma acc kernels
        {
            for(int i = 0; i < SIZE; i++) {
                device_array[i] = host_array[i];
            }
        }
    }

    // Verify that the copy was successful
    for(int i = 0; i < SIZE; i++) {
        if(host_array[i] != device_array[i]) {
            printf("Copy failed at index %d\n", i);
            return 1;
        }
    }

    printf("Copy succeeded\n");
    return 0;
}