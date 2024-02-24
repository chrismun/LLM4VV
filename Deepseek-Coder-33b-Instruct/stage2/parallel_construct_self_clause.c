#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Parallel region with self clause
    #pragma acc parallel loop self(a)
    for (i = 0; i < N; i++) {
        b[i] = a[i] * 2;
    }

    // Check results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i] * 2) {
            printf("Error at index %d: b[%d] = %d, expected %d\n", i, i, b[i], a[i] * 2);
            return 1; // Return non-zero to indicate failure
        }
    }

    printf("All tests passed.\n");
    return 0; // Return zero to indicate success
}