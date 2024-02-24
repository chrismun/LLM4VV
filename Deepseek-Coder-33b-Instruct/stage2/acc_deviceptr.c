#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array;
    int *device_ptr;
    int i;

    // Initialize host array
    for (i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Allocate device memory and copy host array to device
    device_array = (int*)acc_malloc(N * sizeof(int));
    acc_memcpy_to_device(device_array, host_array, N * sizeof(int));

    // Get device pointer
    device_ptr = acc_deviceptr(host_array);

    // Check if device pointer is the same as device address of the array
    if (device_ptr != device_array) {
        printf("Error: acc_deviceptr returned incorrect device pointer\n");
        return 1;
    }

    printf("Test passed\n");
    return 0;
}