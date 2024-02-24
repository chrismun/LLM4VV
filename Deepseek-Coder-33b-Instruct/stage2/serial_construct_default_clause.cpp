#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000000

int main() {
    int i;
    float a[N], b[N], c[N];

    // Initialize arrays
    for (i = 0; i < N; ++i) {
        a[i] = i * 1.0f;
        b[i] = i * 0.1f;
    }

    // Perform vector addition
    #pragma acc kernels
    for (i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }

    // Verify the results
    for (i = 0; i < N; ++i) {
        if (c[i] != a[i] + b[i]) {
            printf("Verification failed at index %d\n", i);
            return 1; // Return non-zero to indicate failure
        }
    }

    printf("Verification passed\n");
    return 0; // Return zero to indicate success
}