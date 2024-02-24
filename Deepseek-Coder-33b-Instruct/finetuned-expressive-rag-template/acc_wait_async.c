#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform computation in parallel
    #pragma acc parallel loop async(1)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Wait for the computation to complete
    acc_wait_async(1, 1);

    // Check the results
    for (int i = 0; i < N; i++) {
        if (c[i] != 2 * i) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}