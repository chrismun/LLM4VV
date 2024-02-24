#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int i, a[N];

    // Initialize the array
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Use OpenACC to parallelize the loop
    #pragma acc parallel loop seq
    for (i = 0; i < N; i++) {
        a[i] *= 2;
    }

    // Verify the results
    for (i = 0; i < N; i++) {
        if (a[i] != i * 2) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}