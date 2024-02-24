#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N], c[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = i;
    }

    // Perform vector addition
    #pragma acc kernels copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc loop independent
        for (i = 0; i < N; ++i) {
            c[i] = a[i] + b[i];
        }
    }

    // Check results
    for (i = 0; i < N; ++i) {
        if (c[i] != a[i] + b[i]) {
            printf("Error at index %d: %d + %d != %d\n", i, a[i], b[i], c[i]);
            return 1; // Return non-zero to indicate failure
        }
    }

    printf("All tests passed.\n");
    return 0; // Return zero to indicate success
}