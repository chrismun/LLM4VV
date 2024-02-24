#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array = (int*)malloc(N * sizeof(int));
    int i, err = 0;

    // Initialize host array
    for (i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Copy data from host to device
    #pragma acc data copyin(host_array[0:N]) create(device_array[0:N])
    {
        #pragma acc kernels
        for (i = 0; i < N; i++) {
            device_array[i] = host_array[i];
        }
    }

    // Check if data is correctly copied
    for (i = 0; i < N; i++) {
        if (host_array[i] != device_array[i]) {
            err = 1;
            break;
        }
    }

    free(host_array);
    free(device_array);

    return err;
}