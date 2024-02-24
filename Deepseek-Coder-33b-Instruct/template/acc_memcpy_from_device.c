#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array = (int*)malloc(N * sizeof(int));

    // Initialize host array
    for (int i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Copy data from host to device
    #pragma acc data copyin(host_array[:N]) copyout(device_array[:N])
    {
        #pragma acc kernels
        {
            for (int i = 0; i < N; i++) {
                device_array[i] = host_array[i];
            }
        }
    }

    // Verify the data
    for (int i = 0; i < N; i++) {
        if (host_array[i] != device_array[i]) {
            printf("Error: host_array[%d] = %d, device_array[%d] = %d\n", i, host_array[i], i, device_array[i]);
            return 1;
        }
    }

    printf("Data copied successfully from device to host.\n");

    free(host_array);
    free(device_array);

    return 0;
}