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
    device_array = (int*)acc_malloc(N * sizeof(int));
    acc_memcpy_to_device(device_array, host_array, N * sizeof(int));

    // Update device array
    #pragma acc update device(device_array[0:N])

    // Copy device array back to host
    acc_memcpy_from_device(host_array, device_array, N * sizeof(int));

    // Verify update
    for(int i = 0; i < N; i++) {
        if(host_array[i] != i) {
            printf("Update failed at index %d\n", i);
            return 1;
        }
    }

    printf("Update succeeded\n");

    // Free device memory
    acc_free(device_array);
    free(host_array);

    return 0;
}