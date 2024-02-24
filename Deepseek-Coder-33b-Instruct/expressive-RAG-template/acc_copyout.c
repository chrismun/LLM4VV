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

    // Copy host array to device
    #pragma acc data copyin(host_array[0:N]) copyout(device_array[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            device_array[i] = host_array[i];
        }
    }

    // Check if copy was successful
    for (int i = 0; i < N; i++) {
        if (host_array[i] != device_array[i]) {
            printf("Copy failed at index %d\n", i);
            return 1; // Return non-zero to indicate failure
        }
    }

    printf("Copy successful\n");
    return 0; // Return zero to indicate success
}