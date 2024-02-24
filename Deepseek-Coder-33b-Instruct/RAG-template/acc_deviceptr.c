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

    // Allocate device memory
    device_array = (int*)acc_malloc(N * sizeof(int));

    // Copy host array to device
    #pragma acc data copyin(host_array[0:N]) copyout(device_array[0:N])
    {
        // Copy host array to device
        #pragma acc update device(host_array[0:N])

        // Modify device array
        #pragma acc parallel loop
        for(int i = 0; i < N; i++) {
            device_array[i] = host_array[i] * 2;
        }

        // Copy device array back to host
        #pragma acc update self(device_array[0:N])
    }

    // Verify results
    for(int i = 0; i < N; i++) {
        if(device_array[i] != host_array[i] * 2) {
            printf("Error: device_array[%d] = %d, expected %d\n", i, device_array[i], host_array[i] * 2);
            return 1;
        }
    }

    printf("Test passed!\n");

    // Free memory
    free(host_array);
    acc_free(device_array);

    return 0;
}