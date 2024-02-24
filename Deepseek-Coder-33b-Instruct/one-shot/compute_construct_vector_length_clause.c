#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Use OpenACC to parallelize the loop
    #pragma acc parallel loop vector_length(128)
    for (i = 0; i < N; i++) {
        b[i] = a[i];
    }

    // Verify the results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}