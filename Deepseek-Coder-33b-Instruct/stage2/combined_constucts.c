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

    // Perform vector addition using combined construct
    #pragma acc parallel loop
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Check the results
    for (i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            printf("Error at index %d: %d + %d != %d\n", i, a[i], b[i], c[i]);
            return 1; // Return non-zero to indicate failure
        }
    }

    printf("Combined constructs test passed.\n");
    return 0; // Return zero to indicate success
}