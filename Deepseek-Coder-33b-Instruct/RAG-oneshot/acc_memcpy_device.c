#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data_dev_src, *data_dev_dest;
    size_t bytes = SIZE * sizeof(int);

    // Allocate memory on the host
    int *host_src = (int*)malloc(bytes);
    int *host_dest = (int*)malloc(bytes);

    // Initialize host memory
    for(int i = 0; i < SIZE; i++) {
        host_src[i] = i;
    }

    // Allocate memory on the device
    data_dev_src = (int*)acc_malloc(bytes);
    data_dev_dest = (int*)acc_malloc(bytes);

    // Copy data from host to device
    acc_memcpy_device(data_dev_src, host_src, bytes);

    // Copy data from device to device
    acc_memcpy_device(data_dev_dest, data_dev_src, bytes);

    // Copy data from device to host
    acc_memcpy_device(host_dest, data_dev_dest, bytes);

    // Verify the copy
    for(int i = 0; i < SIZE; i++) {
        if(host_dest[i] != i) {
            printf("Error: Copy failed at index %d\n", i);
            return 1;
        }
    }

    printf("Copy succeeded\n");

    // Free memory
    free(host_src);
    free(host_dest);
    acc_free(data_dev_src);
    acc_free(data_dev_dest);

    return 0;
}