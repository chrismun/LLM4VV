#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array;
    int i;

    // Initialize host array
    for(i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Allocate device memory
    device_array = (int*)acc_malloc(N * sizeof(int));

    // Copy data to device
    #pragma acc data copyin(host_array[:N]) copyout(device_array[:N])
    {
        // Copy data to device
        #pragma acc update device(host_array[:N])

        // Delete data from device
        #pragma acc update self(device_array[:N])
    }

    // Check if data is still present in device memory
    for(i = 0; i < N; i++) {
        if(device_array[i] != i) {
            printf("Data not deleted from device memory\n");
            return 1;
        }
    }

    printf("Data deleted from device memory successfully\n");

    // Free device memory
    free(device_array);

    return 0;
}