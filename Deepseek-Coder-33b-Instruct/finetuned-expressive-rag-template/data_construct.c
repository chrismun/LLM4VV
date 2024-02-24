#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = (int*)malloc(N * sizeof(int));
    int i, err = 0;

    // Initialize host data
    for (i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_data[0:N]) copyout(device_data[0:N])
    {
        // Copy data from host to device
        #pragma acc update device(host_data[0:N])

        // Perform computation on device
        #pragma acc parallel loop
        for (i = 0; i < N; i++) {
            device_data[i] = host_data[i];
        }

        // Copy data from device to host
        #pragma acc update self(device_data[0:N])
    }

    // Check that the data was copied correctly
    for (i = 0; i < N; i++) {
        if (host_data[i] != device_data[i]) {
            err = 1;
            break;
        }
    }

    free(host_data);
    free(device_data);

    return err;
}