#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024

int main() {
    int i;
    int *host_array, *device_array;

    // Allocate memory on the host
    host_array = (int *)malloc(NUM_ELEMENTS * sizeof(int));

    // Initialize host_array
    for (i = 0; i < NUM_ELEMENTS; i++) {
        host_array[i] = i;
    }

    // Copy data to the device using acc_copyin
    device_array = (int *)acc_copyin(host_array, NUM_ELEMENTS * sizeof(int));

    // Perform some operations on the device
    #pragma acc parallel loop deviceptr(device_array)
    for (i = 0; i < NUM_ELEMENTS; i++) {
        device_array[i] *= 2;
    }

    // Copy data back to the host using acc_create
    host_array = (int *)acc_create(device_array, NUM_ELEMENTS * sizeof(int));

    // Check the results
    for (i = 0; i < NUM_ELEMENTS; i++) {
        if (host_array[i] != i * 2) {
            printf("Test failed at element %d: expected %d, got %d\n", i, i * 2, host_array[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}