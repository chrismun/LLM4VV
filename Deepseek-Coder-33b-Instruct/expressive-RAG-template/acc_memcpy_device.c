#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a, *b;
    int i;

    // Allocate memory on the host
    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));

    // Initialize the host arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Allocate memory on the device
    #pragma acc enter data copyin(a[0:N], b[0:N])

    // Copy data from a to b on the device
    #pragma acc parallel loop copyout(b[0:N])
    for (i = 0; i < N; i++) {
        b[i] = a[i];
    }

    // Check the results
    for (i = 0; i < N; i++) {
        if (b[i] != i) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], i);
            return 1; // Return non-zero to indicate an error
        }
    }

    // Free the device memory
    #pragma acc exit data delete(a[0:N], b[0:N])

    // Free the host memory
    free(a);
    free(b);

    return 0; // Return zero to indicate success
}