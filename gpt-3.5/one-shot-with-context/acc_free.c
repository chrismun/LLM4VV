#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 10;
    int *data_dev = (int *)acc_malloc(n * sizeof(int));
    if (data_dev == NULL) {
        printf("Failed to allocate memory on the device.\n");
        exit(1);
    }

    // Initialize data on the host
    int *data_host = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        data_host[i] = i;
    }

    // Transfer data from host to device
    acc_memcpy_to_device(data_dev, data_host, n * sizeof(int));

    // Perform operations on the device

    // Free memory on the device
    acc_free(data_dev);

    // Check if memory was successfully freed
    if (data_dev == NULL) {
        printf("Memory successfully freed on the device.\n");
    } else {
        printf("Failed to free memory on the device.\n");
        exit(1);
    }

    // Cleanup
    free(data_host);

    return 0;
}