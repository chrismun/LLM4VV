#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024

int main() {
    int i;
    int *host_array, *device_array;

    // Allocate memory on the host
    host_array = (int *) malloc(NUM_ELEMENTS * sizeof(int));

    // Initialize host_array
    for (i = 0; i < NUM_ELEMENTS; i++) {
        host_array[i] = i;
    }

    // Copy data from host to device
    device_array = (int *) acc_copyin(host_array, NUM_ELEMENTS * sizeof(int));

    // Check if the data has been copied correctly
    for (i = 0; i < NUM_ELEMENTS; i++) {
        if (host_array[i] != device_array[i]) {
            printf("Test failed: host_array[%d] = %d, device_array[%d] = %d\n", i, host_array[i], i, device_array[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}