#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int a[N], b[N], c[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform vector addition in parallel
    #pragma acc parallel loop
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Check the results
    for (i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            printf("Error at index %d\n", i);
            return 1; // Return non-zero to indicate failure
        }
    }

    printf("All tests passed\n");
    return 0; // Return zero to indicate success
}