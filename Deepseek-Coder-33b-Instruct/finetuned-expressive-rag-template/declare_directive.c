#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i;

    // Initialize the arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Use the declare directive to specify that a and b should be copied to the device memory
    #pragma acc declare copyin(a) copyout(b)

    // Perform the computation on the device
    #pragma acc parallel loop
    for (i = 0; i < N; i++) {
        b[i] = a[i] * 2;
    }

    // Check the results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i] * 2) {
            printf("Error at index %d\n", i);
            return 1; // Return non-zero to indicate an error
        }
    }

    printf("All tests passed\n");
    return 0; // Return zero to indicate success
}