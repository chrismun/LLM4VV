#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array = (int*)malloc(N * sizeof(int));

    // Initialize host array
    for(int i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Copy host array to device
    #pragma acc data copyin(host_array[0:N]) copyout(device_array[0:N])
    {
        // Update device array
        #pragma acc update device(device_array[0:N])
    }

    // Verify the update
    for(int i = 0; i < N; i++) {
        if(host_array[i] != device_array[i]) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}