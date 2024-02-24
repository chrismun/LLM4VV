#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i, sum = 0;

    // Initialize the arrays
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // Use OpenACC to sum the array in parallel
    #pragma acc kernels copyin(a[0:N]) copyout(b[0:N])
    {
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    // Check the results
    for (i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            printf("Error: a[%d] = %d, b[%d] = %d\n", i, a[i], i, b[i]);
            return 1; // Return non-zero to indicate failure
        }
    }

    return 0; // Return zero to indicate success
}