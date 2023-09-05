#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 10

int main() {
    int i;
    int *host_array;
    int *device_array;

    // Allocate memory on host
    host_array = (int *)malloc(N * sizeof(int));

    // Allocate memory on device
    acc_malloc((void **)&device_array, N * sizeof(int));

    // Initialize host array
    for (i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Copy host array to device
    acc_memcpy_device(device_array, host_array, N * sizeof(int));

    // Print device array
    #pragma acc parallel loop present(device_array)
    for (i = 0; i < N; i++) {
        printf("%d ", device_array[i]);
    }
    printf("\n");

    // Deallocate memory on device
    acc_free(device_array);

    // Deallocate memory on host
    free(host_array);

    return 0;