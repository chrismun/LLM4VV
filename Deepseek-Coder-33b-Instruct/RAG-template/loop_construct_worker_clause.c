#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i, a[N], b[N], c[N];

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Parallelize loop using OpenACC
    #pragma acc parallel loop worker(1)
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Check results
    for (i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("All tests passed\n");
    return 0;
}