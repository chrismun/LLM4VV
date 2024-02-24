#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int i, j;

    // Initialize array a
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Use OpenACC to parallelize the loop
    #pragma acc parallel loop firstprivate(a) copyout(b)
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