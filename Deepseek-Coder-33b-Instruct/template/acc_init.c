#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    // Initialize the arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Copy the arrays to the GPU
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        // Initialize the array b on the GPU
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    // Verify the results
    for (int i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error at index %d: b[%d] = %d, a[%d] = %d\n", i, i, b[i], i, a[i]);
            return 1;
        }
    }

    printf("Test passed.\n");
    return 0;
}