#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *data = (int*)malloc(N * sizeof(int));
    int *data_device = (int*)malloc(N * sizeof(int));

    // Initialize data on host
    for(int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Copy data to device
    #pragma acc enter data copyin(data[:N])

    // Update data on device
    #pragma acc update device(data[:N])

    // Copy data back to host
    #pragma acc update self(data[:N])

    // Check if update was successful
    for(int i = 0; i < N; i++) {
        if(data[i] != i) {
            printf("Update failed at index %d\n", i);
            return 1; // Return non-zero to indicate failure
        }
    }

    printf("Update successful\n");
    return 0; // Return zero to indicate success
}