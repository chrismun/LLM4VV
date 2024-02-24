#include <stdlib.h>
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
    #pragma acc data copyin(host_data[:N]) copy(device_data[:N])
    {
        // Perform computations on device_data
        #pragma acc kernels present(device_data[:N])
        for (int i = 0; i < N; i++) {
            device_data[i] = host_data[i] * 2;
        }

        // Copy data back to host
        #pragma acc update host(device_data[:N]) if_present
    }

    // Verify results
    for (int i = 0; i < N; i++) {
        if (device_data[i] != host_data[i] * 2) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}