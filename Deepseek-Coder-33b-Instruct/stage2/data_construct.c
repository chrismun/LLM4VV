#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 10

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array = (int*)malloc(N * sizeof(int));
    int i;

    // Initialize host array
    for (i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Copy host array to device
    #pragma acc data copyin(host_array[0:N]) copyout(device_array[0:N])
    {
        // Copy host array to device
        #pragma acc update device(host_array[0:N])

        // Modify device array
        #pragma acc parallel loop
        for (i = 0; i < N; i++) {
            device_array[i] = host_array[i] * 2;
        }

        // Copy device array back to host
        #pragma acc update self(device_array[0:N])
    }

    // Check if device array is correct
    for (i = 0; i < N; i++) {
        if (device_array[i] != host_array[i] * 2) {
            printf("Error: device_array[%d] = %d, expected %d\n", i, device_array[i], host_array[i] * 2);
            return 1;
        }
    }

    printf("Data construct test passed\n");
    return 0;
}