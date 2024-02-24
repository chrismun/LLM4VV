#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_data, *device_data;
    int i, err = 0;

    // Allocate memory on host and device
    host_data = (int*)malloc(N * sizeof(int));
    if (host_data == NULL) {
        printf("Failed to allocate host memory\n");
        return 1;
    }

    device_data = (int*)acc_malloc(N * sizeof(int));
    if (device_data == NULL) {
        printf("Failed to allocate device memory\n");
        free(host_data);
        return 1;
    }

    // Initialize host data
    for (i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Copy data from host to device
    #pragma acc data copyin(host_data[0:N]) copyout(device_data[0:N])
    {
        #pragma acc kernels
        for (i = 0; i < N; i++) {
            device_data[i] = host_data[i];
        }
    }

    // Verify the data
    for (i = 0; i < N; i++) {
        if (device_data[i] != host_data[i]) {
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