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

    // Map data to device
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        // Update device data
        #pragma acc update device(a[0:N])

        // Perform computation
        #pragma acc parallel loop
        for (i = 0; i < N; i++) {
            b[i] = a[i] * 2;
        }
    }

    // Check results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i] * 2) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}