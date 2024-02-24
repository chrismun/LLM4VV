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

    // Create device array
    device_array = (int*)acc_create((void*)host_array, N * sizeof(int));

    // Copy device array back to host
    acc_copyout(host_array, device_array, N * sizeof(int));

    // Verify the copy
    for(int i = 0; i < N; i++) {
        if(host_array[i] != i) {
            printf("Error: host_array[%d] = %d, expected %d\n", i, host_array[i], i);
            return 1;
        }
    }

    printf("Success: host_array and device_array are the same\n");

    // Free memory
    free(host_array);
    acc_delete(device_array, N * sizeof(int));

    return 0;
}