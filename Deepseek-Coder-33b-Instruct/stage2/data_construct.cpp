#include <stdlib.h>
#include <stdio.h>

#ifdef _OPENACC
#include <openacc.h>
#endif

#define N 100

int main() {
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data;

    // Initialize host data
    for (int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Allocate device memory
    #pragma acc data copyin(host_data[0:N]) create(device_data[0:N])
    {
        // Copy data to device
        #pragma acc update device(host_data[0:N])

        // Perform computation on device
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            device_data[i] = host_data[i];
        }

        // Copy data back to host
        #pragma acc update self(device_data[0:N])
    }

    // Verify results
    for (int i = 0; i < N; i++) {
        if (host_data[i] != device_data[i]) {
            printf("Error: host_data[%d] = %d, device_data[%d] = %d\n", i, host_data[i], i, device_data[i]);
            return 1;
        }
    }

    printf("Data construct test passed\n");
    return 0;
}