#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i, err = 0;
    int *data = (int*)malloc(N * sizeof(int));
    int *data_device = (int*)malloc(N * sizeof(int));

    // Initialize data in shared memory
    for (i = 0; i < N; i++) {
        data[i] = i;
    }

    // Copy data to device memory
    #pragma acc enter data copyin(data[0:N])

    // Update data in device memory
    #pragma acc update device(data[0:N])

    // Copy data back to shared memory
    #pragma acc update self(data[0:N])

    // Check if data is correct
    for (i = 0; i < N; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
    }

    // Free memory
    #pragma acc exit data delete(data[0:N])
    free(data);
    free(data_device);

    return err;
}