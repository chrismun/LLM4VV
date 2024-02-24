#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = (int*)malloc(N * sizeof(int));

    // Initialize host_data
    for (int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_data[:N]) copyout(device_data[:N])
    {
        // Use device data in a parallel region
        #pragma acc parallel loop use_device(host_data)
        for (int i = 0; i < N; i++) {
            device_data[i] = host_data[i];
        }
    }

    // Verify the results
    for (int i = 0; i < N; i++) {
        if (device_data[i] != host_data[i]) {
            printf("Error: device_data[%d] = %d, expected %d\n", i, device_data[i], host_data[i]);
            return 1; // Return non-zero to indicate an error
        }
    }

    printf("Test passed\n");
    return 0; // Return zero to indicate success
}