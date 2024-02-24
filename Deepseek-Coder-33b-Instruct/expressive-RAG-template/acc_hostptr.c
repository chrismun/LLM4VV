#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array;
    int *host_ptr;

    // Initialize host array
    for(int i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Allocate device memory
    device_array = (int*)acc_malloc(N * sizeof(int));

    // Copy host array to device
    acc_memcpy_to_device(device_array, host_array, N * sizeof(int));

    // Get host pointer
    host_ptr = acc_hostptr(device_array);

    // Check if host pointer is the same as host array
    if(host_ptr != host_array) {
        printf("Error: acc_hostptr returned incorrect host pointer\n");
        return 1;
    }

    printf("Success: acc_hostptr returned correct host pointer\n");

    // Free device and host memory
    acc_free(device_array);
    free(host_array);

    return 0;
}