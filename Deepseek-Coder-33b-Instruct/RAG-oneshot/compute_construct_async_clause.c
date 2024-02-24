#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Perform computation using OpenACC
    #pragma acc parallel loop async(1)
    for (i = 0; i < N; i++) {
        b[i] = a[i] * 2;
    }

    // Wait for the computation to finish
    #pragma acc wait

    // Verify the results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i] * 2) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}