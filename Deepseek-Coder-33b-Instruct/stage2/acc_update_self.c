#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *data = (int*)malloc(N * sizeof(int));
    int *data_orig = (int*)malloc(N * sizeof(int));
    int i, err = 0;

    // Initialize the array
    for (i = 0; i < N; i++) {
        data[i] = i;
        data_orig[i] = i;
    }

    // Copy the array to the device
    #pragma acc enter data copyin(data[0:N])

    // Update the array on the device
    #pragma acc update self(data[0:N])

    // Copy the array back to the host
    #pragma acc update self(data[0:N])

    // Check if the array is the same as before
    for (i = 0; i < N; i++) {
        if (data[i] != data_orig[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory
    #pragma acc exit data delete(data[0:N])
    free(data);
    free(data_orig);

    return err;
}