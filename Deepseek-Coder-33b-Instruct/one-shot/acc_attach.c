#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = (int*)malloc(N * sizeof(int));

    // Initialize host data
    for(int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_data[0:N]) copyout(device_data[0:N])
    {
        // Update device data with host data
        #pragma acc update device(device_data[0:N])
    }

    // Verify the data
    for(int i = 0; i < N; i++) {
        if(host_data[i] != device_data[i]) {
            printf("Data verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Data verification passed\n");
    return 0;
}