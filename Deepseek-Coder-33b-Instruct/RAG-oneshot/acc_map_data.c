#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *host_array = (int*)malloc(SIZE * sizeof(int));
    int *device_array;

    // Initialize host array
    for(int i = 0; i < SIZE; i++) {
        host_array[i] = i;
    }

    // Allocate device memory
    device_array = (int*)acc_malloc(SIZE * sizeof(int));

    // Map device memory to host array
    acc_map_data(host_array, device_array, SIZE * sizeof(int));

    // Check if data is correctly mapped
    for(int i = 0; i < SIZE; i++) {
        if(host_array[i] != device_array[i]) {
            printf("Data is not correctly mapped at index %d\n", i);
            return 1;
        }
    }

    printf("Data is correctly mapped\n");

    // Unmap data
    acc_unmap_data(host_array);

    // Free device memory
    acc_free(device_array);

    // Free host array
    free(host_array);

    return 0;
}