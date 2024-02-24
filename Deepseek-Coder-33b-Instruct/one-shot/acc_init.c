#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    // Initialize data on the host
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Copy data to the device and initialize b
    #pragma acc data copyin(a[0:N]) copy(b[0:N])
    {
        #pragma acc enter data copyin(b[0:N])

        // Perform computation
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            b[i] = a[i];
        }

        // Exit data section
        #pragma acc exit data copyout(b[0:N])
    }

    // Check the results
    for (int i = 0; i < N; i++) {
        if (b[i] != i) {
            printf("Error at index %d: expected %d, got %d\n", i, i, b[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}