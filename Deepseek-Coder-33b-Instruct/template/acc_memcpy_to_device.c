#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array, *device_array;
    int i;

    // Allocate memory on the host
    host_array = (int*)malloc(N * sizeof(int));
    if (host_array == NULL) {
        printf("Memory allocation failed on host\n");
        return 1;
    }

    // Initialize host array
    for (i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Allocate memory on the device
    device_array = (int*)acc_malloc(N * sizeof(int));
    if (device_array == NULL) {
        printf("Memory allocation failed on device\n");
        return 1;
    }

    // Copy data from host to device
    acc_memcpy_to_device(device_array, host_array, N * sizeof(int));

    // Free memory on the host
    free(host_array);

    // Free memory on the device
    acc_free(device_array);

    return 0;
}