#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array;

    // Initialize host array
    for(int i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Allocate device memory and copy host array to device
    #pragma acc enter data create(device_array[0:N])
    #pragma acc update device(host_array[0:N])

    // Use host_array on the device
    #pragma acc parallel loop present(device_array[0:N])
    for(int i = 0; i < N; i++) {
        device_array[i] *= 2;
    }

    // Copy device array back to host
    #pragma acc update host(device_array[0:N])

    // Verify the results
    for(int i = 0; i < N; i++) {
        if(device_array[i] != i * 2) {
            printf("Error: device_array[%d] = %d, expected %d\n", i, device_array[i], i * 2);
            return 1;
        }
    }

    printf("Test passed!\n");

    // Free device memory
    #pragma acc exit data delete(device_array[0:N])

    free(host_array);

    return 0;
}