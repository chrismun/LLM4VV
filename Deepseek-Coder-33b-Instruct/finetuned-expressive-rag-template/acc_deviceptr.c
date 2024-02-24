#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array = NULL;
    int *device_ptr = NULL;

    // Initialize host array
    for (int i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Allocate device array
    device_array = (int*)acc_malloc(N * sizeof(int));

    // Copy host array to device
    #pragma acc data copyin(host_array[0:N]) copyout(device_array[0:N])
    {
        // Get device pointer
        device_ptr = acc_deviceptr(host_array);

        // Check that device pointer is not null
        if (device_ptr == NULL) {
            printf("Error: device pointer is null\n");
            return 1;
        }

        // Copy data from host to device
        #pragma acc parallel loop present(host_array, device_array)
        for (int i = 0; i < N; i++) {
            device_array[i] = host_array[i];
        }
    }

    // Check that data in device array matches data in host array
    for (int i = 0; i < N; i++) {
        if (device_array[i] != host_array[i]) {
            printf("Error: data in device array does not match data in host array\n");
            return 1;
        }
    }

    // Free device and host arrays
    acc_free(device_array);
    free(host_array);

    return 0;
}