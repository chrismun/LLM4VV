#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array;

    // Initialize host array
    for(int i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Allocate memory on the device
    device_array = (int*)acc_malloc(N * sizeof(int));

    // Copy data from host to device
    #pragma acc data copyin(host_array[:N]) copyout(device_array[:N])
    {
        // Copy data from host to device
        #pragma acc update device(host_array[:N])

        // Perform some computation on the device
        #pragma acc parallel loop
        for(int i = 0; i < N; i++) {
            device_array[i] = host_array[i] * 2;
        }

        // Copy data from device to host
        #pragma acc update self(device_array[:N])
    }

    // Verify the results
    for(int i = 0; i < N; i++) {
        if(device_array[i] != host_array[i] * 2) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");

    // Free memory
    free(host_array);
    acc_free(device_array);

    return 0;
}