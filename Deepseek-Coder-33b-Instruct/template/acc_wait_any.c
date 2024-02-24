#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N], c[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    // Parallelize the addition operation
    #pragma acc parallel loop
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Wait for all devices to finish
    #pragma acc wait

    // Verify the results
    for (i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("All tests passed.\n");
    return 0;
}