#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = NULL;

    // Initialize host data
    for (int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Allocate device memory and copy host data to device
    #pragma acc enter data create(device_data[0:N])
    #pragma acc update device(host_data[0:N])

    // Get the host pointer associated with the device memory
    int *host_ptr = acc_hostptr(device_data);

    // Check if the host pointer is the same as the host data
    if (host_ptr != host_data) {
        printf("Error: acc_hostptr returned incorrect host pointer\n");
        return 1;
    }

    // Free device memory
    #pragma acc exit data delete(device_data[0:N])

    // Free host memory
    free(host_data);

    return 0;
}