#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i, a[N], b[N];

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Use OpenACC to parallelize the loop
    #pragma acc parallel loop gang
    for (i = 0; i < N; i++) {
        b[i] = a[i] * 2;
    }

    // Check the results
    for (i = 0; i < N; i++) {
        if (b[i] != i * 2) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("All tests passed.\n");
    return 0;
}