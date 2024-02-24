#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *data = (int*)malloc(N * sizeof(int));
    int *data_device = (int*)malloc(N * sizeof(int));
    int i, err = 0;

    // Initialize data
    for (i = 0; i < N; i++) {
        data[i] = i;
    }

    // Copy data to device
    #pragma acc enter data copyin(data[:N])

    // Update data in device memory
    #pragma acc update self(data[:N])

    // Copy data from device to host
    #pragma acc update self(data[:N])

    // Check if data is the same
    for (i = 0; i < N; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
    }

    // Free memory
    #pragma acc exit data delete(data[:N])
    free(data);
    free(data_device);

    return err;
}