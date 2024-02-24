#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *data = (int*)malloc(N * sizeof(int));
    int *data_device = (int*)malloc(N * sizeof(int));
    int i;

    // Initialize data
    for (i = 0; i < N; i++) {
        data[i] = i;
    }

    // Copy data to device memory
    #pragma acc data copyin(data[0:N]) create(data_device[0:N])
    {
        #pragma acc update device(data[0:N])

        // Copy data from device memory to shared memory
        #pragma acc update self(data_device[0:N])

        // Delete data from device memory
        #pragma acc update self(data_device[0:N])
    }

    // Check if data is still in shared memory
    for (i = 0; i < N; i++) {
        if (data[i] != i) {
            printf("Error: data is not in shared memory\n");
            return 1;
        }
    }

    printf("Success: data is in shared memory\n");
    return 0;
}