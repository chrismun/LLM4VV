#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

void acc_memcpy_device_test() {
    int *host_data = (int *)malloc(SIZE * sizeof(int));
    int *device_data = (int *)acc_malloc(SIZE * sizeof(int));

    // Initialize host data
    for (int i = 0; i < SIZE; i++) {
        host_data[i] = i;
    }

    // Copy data from host to device
    acc_memcpy_device(device_data, host_data, SIZE * sizeof(int));

    // Copy data from device to host
    int *result_data = (int *)malloc(SIZE * sizeof(int));
    acc_memcpy_device(result_data, device_data, SIZE * sizeof(int));

    // Verify the result
    for (int i = 0; i < SIZE; i++) {
        if (result_data[i] != host_data[i]) {
            printf("Error: data mismatch at index %d\n", i);
        }
    }

    // Free memory
    free(host_data);
    free(result_data);
    acc_free(device_data);
}

int main() {
    acc_memcpy_device_test();

    return 0;