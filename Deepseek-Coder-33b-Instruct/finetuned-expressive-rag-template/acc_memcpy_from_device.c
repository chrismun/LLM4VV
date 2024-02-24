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

    // Copy host array to device array
    #pragma acc enter data copyin(host_array[0:N]) create(device_array[0:N])

    // Copy data from device array to host array
    #pragma acc update device(host_array[0:N])

    // Verify that the data was copied correctly
    for (int i = 0; i < N; i++) {
        if (host_array[i] != device_array[i]) {
            printf("Error: Data not copied correctly\n");
            return 1;
        }
    }

    printf("Data copied correctly\n");

    // Free memory
    #pragma acc exit data delete(host_array[0:N], device_array[0:N])

    free(host_array);
    free(device_array);

    return 0;
}