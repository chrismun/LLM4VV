#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data;

    // Initialize host data
    for(int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Allocate device memory
    device_data = (int*)acc_malloc(N * sizeof(int));

    // Map host data to device data
    acc_map_data(host_data, device_data, N * sizeof(int));

    // Use device data in a parallel region
    #pragma acc parallel loop
    for(int i = 0; i < N; i++) {
        device_data[i] *= 2;
    }

    // Unmap data
    acc_unmap_data(host_data);

    // Check results
    for(int i = 0; i < N; i++) {
        if(host_data[i] != i * 2) {
            printf("Error: host_data[%d] = %d, expected %d\n", i, host_data[i], i * 2);
            return 1; // Return non-zero to indicate an error
        }
    }

    // Clean up
    free(host_data);
    acc_free(device_data);

    return 0; // Return zero to indicate success
}