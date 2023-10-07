#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i;
    int *data = (int *)malloc(N * sizeof(int));

    // Initialize data
    for (i = 0; i < N; i++) {
        data[i] = i;
    }

    // Copy data to GPU
    #pragma acc enter data copyin(data[0:N])

    // Perform computations on GPU
    #pragma acc parallel loop present_or_copyout(data[0:N])
    for (i = 0; i < N; i++) {
        data[i] *= 2;
    }

    // Copy data back to CPU
    #pragma acc exit data copyout(data[0:N])

    // Check result
    for (i = 0; i < N; i++) {
        if (data[i] != i * 2) {
            printf("Error: Data is incorrect!\n");
            return 1;
        }
    }

    printf("Success: Data is correct!\n");

    return 0;
}