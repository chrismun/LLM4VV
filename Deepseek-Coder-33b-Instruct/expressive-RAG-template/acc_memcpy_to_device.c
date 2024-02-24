#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_data, *device_data;
    int i, err = 0;

    // Allocate memory on the host
    host_data = (int*)malloc(N * sizeof(int));
    if (host_data == NULL) {
        printf("Failed to allocate host memory\n");
        return 1;
    }

    // Initialize host data
    for (i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Allocate memory on the device
    device_data = (int*)acc_malloc(N * sizeof(int));
    if (device_data == NULL) {
        printf("Failed to allocate device memory\n");
        free(host_data);
        return 1;
    }

    // Copy data from host to device
    acc_memcpy_to_device(device_data, host_data, N * sizeof(int));

    // Verify the data on the device
    acc_memcpy_from_device(host_data, device_data, N * sizeof(int));
    for (i = 0; i < N; i++) {
        if (host_data[i] != i) {
            printf("Data verification failed at index %d\n", i);
            err = 1;
            break;
        }
    }

    // Free memory
    free(host_data);
    acc_free(device_data);

    return err;
}